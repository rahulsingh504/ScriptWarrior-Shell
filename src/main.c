#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "scriptwarrior_shell.h"
#include "alias.h"
#include "history.h"
#include "auth.h"

#define MAX_CMD_LEN 1024
#define MAX_ARGS 100

int executeSingleCommand(char *input);

void executeChainedCommands(char *input) {
    char *cmd = input;
    char *next;
    int last_status = 0;
    while (cmd && *cmd) {
        next = strpbrk(cmd, ";|&");
        char op = 0;
        if (next) {
            op = *next;
            *next = '\0';
        }
        while (*cmd == ' ') cmd++;
        char *end = cmd + strlen(cmd) - 1;
        while (end > cmd && *end == ' ') *end-- = '\0';

        if (op == '&' && next[1] == '&') {
            if (last_status == 0) executeSingleCommand(cmd);
            cmd = next + 2;
        } else if (op == '|' && next[1] == '|') {
            if (last_status != 0) executeSingleCommand(cmd);
            cmd = next + 2;
        } else {
            last_status = executeSingleCommand(cmd);
            if (op == ';' || op == '&' || op == '|') cmd = next + 1;
            else break;
        }
    }
}

int executeSingleCommand(char *input) {
    int background = 0;
    char *amp = strrchr(input, '&');
    if (amp && *(amp + 1) == '\0') {
        background = 1;
        *amp = '\0';
    }
    char *pipe_pos = strchr(input, '|');
    if (pipe_pos) {
        int fd[2];
        pipe(fd);
        *pipe_pos = '\0';
        pid_t pid1 = fork();
        if (pid1 == 0) {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]); close(fd[1]);
            executeSingleCommand(input);
            exit(0);
        }
        pid_t pid2 = fork();
        if (pid2 == 0) {
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]); close(fd[1]);
            executeSingleCommand(pipe_pos + 1);
            exit(0);
        }
        close(fd[0]); close(fd[1]);
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        return 0;
    }
    char *infile = NULL, *outfile = NULL;
    int append = 0;
    char *redir;
    if ((redir = strstr(input, ">>"))) {
        *redir = '\0'; outfile = redir + 2; append = 1;
    } else if ((redir = strchr(input, '>'))) {
        *redir = '\0'; outfile = redir + 1; append = 0;
    }
    if ((redir = strchr(input, '<'))) {
        *redir = '\0'; infile = redir + 1;
    }
    if (outfile) while (*outfile == ' ') outfile++;
    if (infile) while (*infile == ' ') infile++;
    char *args[MAX_ARGS]; int i = 0;
    char *tok = strtok(input, " ");
    while (tok && i < MAX_ARGS - 1) args[i++] = tok, tok = strtok(NULL, " ");
    args[i] = NULL;
    pid_t pid = fork();
    if (pid == 0) {
        if (infile) {
            int fd = open(infile, O_RDONLY);
            if (fd < 0) { perror("open infile"); exit(1); }
            dup2(fd, STDIN_FILENO); close(fd);
        }
        if (outfile) {
            int fd = open(outfile, O_WRONLY | O_CREAT | (append ? O_APPEND : O_TRUNC), 0644);
            if (fd < 0) { perror("open outfile"); exit(1); }
            dup2(fd, STDOUT_FILENO); close(fd);
        }
        execvp(args[0], args);
        perror("execvp");
        exit(1);
    }
    if (!background) waitpid(pid, NULL, 0);
    return 0;
}

void executeCommandWithRedirection(char *input) {
    executeSingleCommand(input);
}

void executeScript(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { perror("Script open failed"); return; }
    char line[MAX_CMD_LEN];
    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = '\0';
        executeCommandWithRedirection(line);
    }
    fclose(fp);
}

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("Welcome to ScriptWarrior Shell!\nType 'exit' to quit.\n\n");
    fflush(stdout);
    authenticateUser();
    char input[MAX_CMD_LEN];
    while (1) {
        displayPrompt();
        if (fgets(input, sizeof(input), stdin) == NULL) { perror("Error reading input"); continue; }
        input[strcspn(input, "\n")] = '\0';
        addHistory(input);
        if (strstr(input, ".myscript") != NULL) { executeScript(input); continue; }
        expandAlias(input);
        if (strpbrk(input, ";|&")) { executeChainedCommands(input); continue; }
        if (strcmp(input, "exit") == 0) break;
        else if (strcmp(input, "automate") == 0) automateTask();
        else if (strncmp(input, "fcfs", 4) == 0) {
            char *args[MAX_ARGS]; int i = 0;
            args[i] = strtok(input, " ");
            while (args[i] != NULL && i < MAX_ARGS - 1) args[++i] = strtok(NULL, " ");
            if (i > 1) fcfsScheduler(&args[1], i - 1);
            else printf("Usage: fcfs command1 command2 ...\n");
        }
        else if (strncmp(input, "rr", 2) == 0) {
            char *args[MAX_ARGS]; int i = 0;
            args[i] = strtok(input, " ");
            while (args[i] != NULL && i < MAX_ARGS - 1) args[++i] = strtok(NULL, " ");
            if (i > 2) {
                int quantum = atoi(args[1]);
                roundRobinScheduler(&args[2], i - 2, quantum);
            } else printf("Usage: rr <quantum> command1 command2 ...\n");
        }
        else executeCommandWithRedirection(input);
    }
    return 0;
}