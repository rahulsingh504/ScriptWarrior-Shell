#include <stdio.h>
#include <string.h>
#include "alias.h"

#define MAX_ALIASES 100
#define MAX_ALIAS_LEN 256

typedef struct {
    char name[MAX_ALIAS_LEN];
    char command[MAX_ALIAS_LEN];
} Alias;

static Alias aliases[MAX_ALIASES];
static int alias_count = 0;

void addAlias(const char *name, const char *command) {
    if (alias_count < MAX_ALIASES) {
        strncpy(aliases[alias_count].name, name, MAX_ALIAS_LEN);
        strncpy(aliases[alias_count].command, command, MAX_ALIAS_LEN);
        alias_count++;
    }
}

void expandAlias(char *input) {
    for (int i = 0; i < alias_count; i++) {
        if (strncmp(input, aliases[i].name, strlen(aliases[i].name)) == 0) {
            char temp[MAX_ALIAS_LEN * 2];
            snprintf(temp, sizeof(temp), "%s%s", aliases[i].command, input + strlen(aliases[i].name));
            strcpy(input, temp);
            break;
        }
    }
}