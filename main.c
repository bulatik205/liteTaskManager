#include <stdio.h>
#include <time.h>
#define MAX_TEXT_LENGHT 1000
#define FILE_WITH_TASKS "tasks.txt"
#define FILE_WITH_LOG "log.txt"

#define ERROR_RANGE < 0
#define ERROR 0
#define SUCCESS 1

#define ERROR_NOT_ENOUGH_RIGHT_TO_WRITE "Not enough rights for write"
#define ERROR_WRITING_IN_FILE "Fail at writing in file"

time_t getTime(void)
{
    return time(NULL);
}

FILE *getFile(const char *filePath, const char *openMethod)
{
    return fopen(filePath, openMethod);
}

void logger(char *message)
{
    FILE *logFile = getFile(FILE_WITH_LOG, "a");
    if (logFile == NULL)
    {
        printf("Logger error: %s, in dir: %s\n", ERROR_NOT_ENOUGH_RIGHT_TO_WRITE, FILE_WITH_LOG);
        return;
    }

    fprintf(logFile, "%lld - log: %s", getTime(), message);
    fclose(logFile);
}

int fileIsExists(const char *filePath)
{
    FILE *searchedFile = getFile(filePath, "r");
    if (searchedFile == NULL)
    {
        return ERROR;
    }
    fclose(searchedFile);
    return SUCCESS;
}

int writeLineInFile(const char *filePath, const char *line)
{
    FILE *writenFile = getFile(filePath, "a");
    if (writenFile == NULL)
    {
        logger(ERROR_NOT_ENOUGH_RIGHT_TO_WRITE);
        return ERROR;
    }

    if (fprintf(writenFile, "%s", line) ERROR_RANGE)
    {
        logger(ERROR_WRITING_IN_FILE);
        return ERROR;
    }
    fclose(writenFile);
    return SUCCESS;
}

int newTask(const char *filePath, char *text)
{
    if (fileIsExists(filePath) == ERROR)
    {
        logger(ERROR_NOT_ENOUGH_RIGHT_TO_WRITE);
        return ERROR;
    }

    if (writeLineInFile(filePath, text) == ERROR)
    {
        return ERROR;
    }

    return SUCCESS;
}

int getInput(char *buf, int size)
{
    if (fgets(buf, size, stdin) == NULL)
    {
        return ERROR;
    }
    return SUCCESS;
}

int main(void)
{
    char input[MAX_TEXT_LENGHT];
    if (getInput(input, sizeof(input)) == ERROR)
    {
        printf("An error has occurred\n");
        return 1;
    }

    if (newTask(FILE_WITH_TASKS, input) == ERROR)
    {
        printf("An error has occurred\n");
        return 1;
    }
}