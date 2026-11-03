#ifndef APP_H
#define APP_H

#define MAX_TEXT_LENGTH 1000

#ifndef TASKS_PATH
#define TASKS_PATH "tasks.txt"
#endif

#ifndef LOG_PATH
#define LOG_PATH "log.txt"
#endif

#define ERROR   1
#define SUCCESS 0

int writeLineInFile(const char *path, const char *line);
int newTask(const char *path, const char *text);
int getInput(char *buf, int size);
void logger(const char *msg);
#endif