#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "commands.h"

void executeCommand(char *input) {
    char *args[MAX_ARGS];
    int i = 0;

    args[i] = strtok(input, " ");
    while (args[i] != NULL && i < MAX_ARGS - 1) {
        args[++i] = strtok(NULL, " ");
    }
    args[i] = NULL;

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        if (execvp(args[0], args) < 0) {
            perror("Command execution failed");
            exit(1);
        }
    } else {
        if (wait(NULL) < 0) {
            perror("Wait failed");
        }
    }
}