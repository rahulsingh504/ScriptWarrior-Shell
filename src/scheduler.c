#include <stdio.h>
#include <stdlib.h>
#include "scheduler.h"

// Simulates First-Come-First-Serve (FCFS) scheduling
void fcfsScheduler(char *commands[], int n) {
    if (commands == NULL || n <= 0) {
        fprintf(stderr, "Error: Invalid commands or command count.\n");
        return;
    }

    printf("Simulating FCFS Scheduling:\n");
    for (int i = 0; i < n; i++) {
        if (commands[i] != NULL) {
            printf("Running: %s\n", commands[i]);
            if (system(commands[i]) == -1) {
                perror("Error executing command");
            }
        }
    }
}

// Simulates Round Robin scheduling
void roundRobinScheduler(char *commands[], int n, int quantum) {
    if (commands == NULL || n <= 0 || quantum <= 0) {
        fprintf(stderr, "Error: Invalid commands, command count, or quantum.\n");
        return;
    }

    printf("Simulating Round Robin Scheduling with Quantum = %d\n", quantum);
    int remaining = n;

    while (remaining > 0) {
        for (int i = 0; i < n; i++) {
            if (commands[i] != NULL) {
                printf("Running: %s\n", commands[i]);
                if (system(commands[i]) == -1) {
                    perror("Error executing command");
                }
                commands[i] = NULL;
                remaining--;
            }
        }
    }
}