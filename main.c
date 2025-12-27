#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "browser_history.h"

int main() {
    setbuf(stdout, NULL);
    char command[50];
    char arg_str[100];
    int arg_int;
    BrowserHistory* obj = NULL;

    // Loop to read commands from Standard Input
    while (scanf("%s", command) != EOF) {

        if (strcmp(command, "browserHistoryCreate") == 0) {
            scanf("%s", arg_str);
            obj = browserHistoryCreate(arg_str);
            printf("null\n");

        } else if (strcmp(command, "browserHistoryVisit") == 0) {
            scanf("%s", arg_str);
            browserHistoryVisit(obj, arg_str);
            printf("null\n");

        } else if (strcmp(command, "browserHistoryBack") == 0) {
            scanf("%d", &arg_int);
            char* res = browserHistoryBack(obj, arg_int);
            printf("%s\n", res);

        } else if (strcmp(command, "browserHistoryForward") == 0) {
            scanf("%d", &arg_int);
            char* res = browserHistoryForward(obj, arg_int);
            printf("%s\n", res);
        }
    }

    if (obj) browserHistoryFree(obj);
    return 0;
}