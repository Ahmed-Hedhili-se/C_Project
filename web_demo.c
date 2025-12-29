#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "browser_history.h"

int main() {
    // 1. FIX BUFFERING: Force printf to show text immediately
    setbuf(stdout, NULL);
    setbuf(stdin, NULL);

    printf("======================================\n");
    printf("   WebAssembly Browser History Demo   \n");
    printf("======================================\n");
    printf("Commands:\n");
    printf("  visit <url>  : Visit a new page\n");
    printf("  back <steps> : Go back steps\n");
    printf("  fwd <steps>  : Go forward steps\n");
    printf("  quit         : Exit\n");
    printf("--------------------------------------\n");

    BrowserHistory *obj = browserHistoryCreate("homepage.com");
    printf("Start Page: homepage.com\n");

    char command[100];
    char arg[100];

    while (1) {
        printf("\n> ");

        // 2. FIX INFINITE LOOP: Check if input actually works
        int result = scanf("%s", command);

        // If user clicks "Cancel" or input fails, stop the loop!
        if (result <= 0) {
            break;
        }

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
            printf("Exiting...\n");
            break;
        }
        else {
            printf("Unknown command.\n");
        }
    }

    browserHistoryFree(obj);
    return 0;
}