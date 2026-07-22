#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "auth.h"

void authenticateUser() {
    const char correct_username[] = "admin";
    const char correct_password[] = "1234";
    char username[64], password[64];

    printf("Username: ");
    fflush(stdout);
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Password: ");
    fflush(stdout);
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (strcmp(username, correct_username) != 0 || strcmp(password, correct_password) != 0) {
        printf("Authentication failed. Exiting.\n");
        exit(1);
    }
}