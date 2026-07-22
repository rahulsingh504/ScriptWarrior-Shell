// commands.h
#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_ARGS 100

/**
 * Executes a command provided by the user.
 * 
 * @param input The command string to be executed.
 */
void executeCommand(char *input);

#endif // COMMANDS_H