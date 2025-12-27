#include <stdio.h>
#include <string.h>
#include "browser_history.h"

int main() {
    char command[10];
    char url[100];
    int steps;


    BrowserHistory* obj = NULL;

    // Simple interactive loop for the test runner
    while (scanf("%s", command) != EOF) {

        // 1. Initialize
        if (strcmp(command, "START") == 0) {
            scanf("%s", url);
            obj = browserHistoryCreate(url);
            printf("null\n"); // Standard return for void/init methods
        }

        // 2. Visit
        else if (strcmp(command, "VISIT") == 0) {
            scanf("%s", url);
            if (obj) {
                browserHistoryVisit(obj, url);
                printf("null\n");
            }
        }

        // 3. Back
        else if (strcmp(command, "BACK") == 0) {
            scanf("%d", &steps);
            if (obj) {
                char* result = browserHistoryBack(obj, steps);
                printf("%s\n", result);
            }
        }

        // 4. Forward
        else if (strcmp(command, "FORWARD") == 0) {
            scanf("%d", &steps);
            if (obj) {
                char* result = browserHistoryForward(obj, steps);
                printf("%s\n", result);
            }
        }

        // 5. Exit/Free
        else if (strcmp(command, "EXIT") == 0) {
            if (obj) {
                browserHistoryFree(obj);
            }
            break;
        }
    }

    return 0;
}