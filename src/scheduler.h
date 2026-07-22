// filepath: /scriptwarrior_shell/scriptwarrior_shell/src/scheduler.h
#ifndef SCHEDULER_H
#define SCHEDULER_H

void fcfsScheduler(char *commands[], int n);

void roundRobinScheduler(char *commands[], int n, int quantum);

#endif