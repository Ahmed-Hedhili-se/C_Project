#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "browser_history.h"

// Simple helper to remove newline characters
void clean_input(char *str) {
    size_t len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
        str[len-1] = '\0';
    }
}

int main() {
    printf("======================================\n");
    printf("   WebAssembly Browser History Demo   \n");
    printf("======================================\n");
    printf("Commands:\n");
    printf("  visit <url>  : Visit a new page\n");
    printf("  back <steps> : Go back steps\n");
    printf("  fwd <steps>  : Go forward steps\n");
    printf("  current      : Show current page\n");
    printf("  quit         : Exit\n");
    printf("--------------------------------------\n");

    // Initialize your history structure
    // (Adjust this line if your init function has a different name!)
    BrowserHistory *obj = browserHistoryCreate("homepage.com");

    char command[100];
    char arg[100];

    while (1) {
        printf("\n> ");
        if (scanf("%s", command) == EOF) break;

        if (strcmp(command, "visit") == 0) {
            scanf("%s", arg);
            browserHistoryVisit(obj, arg);
            printf("Visited: %s\n", arg);
        }
        else if (strcmp(command, "back") == 0) {
            int steps;
            scanf("%d", &steps);
            char* result = browserHistoryBack(obj, steps);
            printf("Current Page: %s\n", result);
        }
        else if (strcmp(command, "fwd") == 0) {
            int steps;
            scanf("%d", &steps);
            char* result = browserHistoryForward(obj, steps);
            printf("Current Page: %s\n", result);
        }
        else if (strcmp(command, "quit") == 0) {
            break;
        }
        else {
            printf("Unknown command. Try: visit, back, fwd\n");
        }
    }

    // Cleanup (optional for web demo but good practice)
    browserHistoryFree(obj);
    return 0;
}