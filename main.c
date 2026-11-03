#include <stdio.h>
#include "app.h"

int main(void) {
    char input[MAX_TEXT_LENGTH];
    if (getInput(input, sizeof input) == ERROR) {
        printf("An error has occurred\n");
        return 1;
    }
    if (newTask(TASKS_PATH, input) == ERROR) {
        printf("An error has occurred\n");
        return 1;
    }
    return 0;
}