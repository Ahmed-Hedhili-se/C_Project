#include <stdio.h>
#include <stdlib.h>
#include "browser_history.h"

int main() {
    // Force output to appear immediately
    setbuf(stdout, NULL);

    printf("======================================\n");
    printf("   WebAssembly Browser History Demo   \n");
    printf("   (Automatic Simulation Mode)        \n");
    printf("======================================\n\n");

    // 1. Initialize
    BrowserHistory *obj = browserHistoryCreate("homepage.com");
    printf("[Start]  Current Page: homepage.com\n");

    // 2. Visit sites
    printf("\n> Command: visit youtube.com\n");
    browserHistoryVisit(obj, "youtube.com");
    printf("   Output: You are now at youtube.com\n");

    printf("\n> Command: visit github.com\n");
    browserHistoryVisit(obj, "github.com");
    printf("   Output: You are now at github.com\n");

    // 3. Go Back
    printf("\n> Command: back 1\n");
    char* res = browserHistoryBack(obj, 1);
    printf("   Output: Returned to %s\n", res);

    // 4. Go Back again
    printf("\n> Command: back 1\n");
    res = browserHistoryBack(obj, 1);
    printf("   Output: Returned to %s\n", res);

    // 5. Go Forward
    printf("\n> Command: fwd 1\n");
    res = browserHistoryForward(obj, 1);
    printf("   Output: Forward to %s\n", res);

    // Cleanup
    browserHistoryFree(obj);

    printf("\n======================================\n");
    printf("   Simulation Complete. Success!      \n");
    printf("======================================\n");

    return 0;
}