#include <stdio.h>
#include <string.h>
#include "browser_history.h"

void assertEqual(char* result, char* expected, char* testName) {
    if (strcmp(result, expected) == 0) {
        printf("[PASS] %s\n", testName);
    } else {
        printf("[FAIL] %s  (Got: %s , Expected: %s)\n",
                testName, result, expected);
    }
}

int main() {

    printf("===== Running BrowserHistory Unit Tests =====\n\n");

    BrowserHistory* obj = browserHistoryCreate("leetcode.com");

    // Visit "google.com"
    browserHistoryVisit(obj, "google.com");
    browserHistoryVisit(obj, "facebook.com");
    browserHistoryVisit(obj, "youtube.com");

    // BACK 1 → expect facebook
    char* r1 = browserHistoryBack(obj, 1);
    assertEqual(r1, "facebook.com", "Back 1 step");

    // BACK 1 → expect google
    char* r2 = browserHistoryBack(obj, 1);
    assertEqual(r2, "google.com", "Back 1 again");

    // FORWARD 1 → expect facebook
    char* r3 = browserHistoryForward(obj, 1);
    assertEqual(r3, "facebook.com", "Forward 1 step");

    // VISIT "linkedin"
    browserHistoryVisit(obj, "linkedin.com");

    // FORWARD 2 → should remain on linkedin
    char* r4 = browserHistoryForward(obj, 2);
    assertEqual(r4, "linkedin.com", "Forward 2 after visit");

    // BACK 2 → google
    char* r5 = browserHistoryBack(obj, 2);
    assertEqual(r5, "google.com", "Back 2 steps");

    // BACK 7 → leetcode
    char* r6 = browserHistoryBack(obj, 7);
    assertEqual(r6, "leetcode.com", "Back 7 steps");

    browserHistoryFree(obj);

    printf("\n===== Tests Completed =====\n");

    return 0;
}
