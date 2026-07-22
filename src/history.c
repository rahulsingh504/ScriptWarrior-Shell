#include <stdio.h>
#include <string.h>
#include "history.h"

#define MAX_HISTORY 100
static char history[MAX_HISTORY][1024];
static int history_count = 0;

void addHistory(const char *cmd) {
    if (history_count < MAX_HISTORY) {
        strncpy(history[history_count++], cmd, 1023);
    }
}

void showHistory() {
    for (int i = 0; i < history_count; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}