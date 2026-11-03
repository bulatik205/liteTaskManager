#include "app.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MSG_NOT_ENOUGH_RIGHTS "Not enough rights for write"
#define MSG_WRITING_FAILED "Fail at writing in file"

time_t getTime(void)
{
    return time(NULL);
}

void logger(const char *message)
{
    FILE *logFile = fopen(LOG_PATH, "a");
    if (logFile == NULL)
    {
        printf("Logger error: %s, in dir: %s\n",
               MSG_NOT_ENOUGH_RIGHTS, LOG_PATH);
        return;
    }

    fprintf(logFile, "%lld - log: %s\n", (long long)getTime(), message);
    fclose(logFile);
}

int writeLineInFile(const char *filePath, const char *line)
{
    FILE *writtenFile = fopen(filePath, "a");
    if (writtenFile == NULL)
    {
        logger(MSG_NOT_ENOUGH_RIGHTS);
        return ERROR;
    }

    if (fprintf(writtenFile, "%s\n", line) < 0)
    {
        logger(MSG_WRITING_FAILED);
        fclose(writtenFile);
        return ERROR;
    }

    if (fclose(writtenFile) != 0)
    {
        logger(MSG_WRITING_FAILED);
        return ERROR;
    }

    return SUCCESS;
}

int newTask(const char *filePath, const char *text)
{
    return writeLineInFile(filePath, text);
}

int getInput(char *buf, int size)
{
    if (fgets(buf, size, stdin) == NULL)
    {
        return ERROR;
    }

    buf[strcspn(buf, "\n")] = '\0';
    return SUCCESS;
}