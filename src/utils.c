#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void displayPrompt() {
    printf("ScriptWarrior$ ");
    fflush(stdout);
}
void automateTask() {
    printf("Running automation tasks (file listing + disk usage)...\n");
    
    if (system("ls -l") == -1) {
        perror("Error executing ls command");
    }
    
    if (system("du -sh .") == -1) {
        perror("Error executing du command");
    }
}