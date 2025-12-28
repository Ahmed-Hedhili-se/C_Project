#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "browser_history.h"

// Helper to remove leading/trailing whitespace
void trim(char *s) {
    char *p = s;
    int l = strlen(p);
    while(isspace(p[l - 1])) p[--l] = 0;
    while(*p && isspace(*p)) p++;
    memmove(s, p, l + 1);
}

int main() {
    FILE *file = fopen("deep_test.txt", "r");
    if (!file) {
        printf("❌ Error: Could not open tests.txt\n");
        return 1;
    }

    char line[256];
    BrowserHistory* obj = NULL;
    int passed_count = 0;
    int total_count = 0;
    int all_passed = 1;

    printf("🚀 Starting C Test Driver (Reading tests.txt)...\n");
    printf("--------------------------------------------------\n");

    while (fgets(line, sizeof(line), file)) {
        // Skip empty lines
        if (strlen(line) < 3) continue;

        // 1. Split line by '|' to get Command vs Expected
        char *delimiter = strchr(line, '|');
        if (!delimiter) continue; // Invalid line format

        *delimiter = '\0'; // Split the string
        char *command_part = line;
        char *expected_output = delimiter + 1;

        trim(command_part);
        trim(expected_output);

        // 2. Parse Command (e.g., "VISIT google.com")
        char action[50];
        char argument[100];
        // Initialize argument to empty in case it's not present (like EXIT)
        argument[0] = '\0';

        sscanf(command_part, "%s %s", action, argument);

        // 3. Execute Logic
        char actual_output[100] = "null"; // Default return for void functions

        if (strcmp(action, "START") == 0) {
            obj = browserHistoryCreate(argument);
        }
        else if (strcmp(action, "VISIT") == 0) {
            if(obj) browserHistoryVisit(obj, argument);
        }
        else if (strcmp(action, "BACK") == 0) {
            if(obj) {
                int steps = atoi(argument);
                char* res = browserHistoryBack(obj, steps);
                strcpy(actual_output, res ? res : "null");
            }
        }
        else if (strcmp(action, "FORWARD") == 0) {
            if(obj) {
                int steps = atoi(argument);
                char* res = browserHistoryForward(obj, steps);
                strcpy(actual_output, res ? res : "null");
            }
        }
        else if (strcmp(action, "EXIT") == 0) {
            if(obj) browserHistoryFree(obj);
            break;
        }

        // 4. Compare Results
        total_count++;
        if (strcmp(actual_output, expected_output) == 0) {
            printf("✅ %-25s | PASS\n", command_part);
            passed_count++;
        } else {
            printf("❌ %-25s | FAIL (Exp: %s, Got: %s)\n", command_part, expected_output, actual_output);
            all_passed = 0;
        }
    }

    fclose(file);

    printf("--------------------------------------------------\n");
    if (all_passed && total_count > 0) {
        printf("🎉 SUCCESS: %d/%d tests passed.\n", passed_count, total_count);
        return 0; // Exit with success
    } else {
        printf("💀 FAILURE: %d tests failed.\n", total_count - passed_count);
        return 1; // Exit with failure (CI will see red)
    }
}
