// browser_history.h
#ifndef BROWSER_HISTORY_H
#define BROWSER_HISTORY_H

typedef struct {
    char* *history;
    int size;
    int capacity;
    int curr;
} BrowserHistory;

BrowserHistory* browserHistoryCreate(char* homepage);
void browserHistoryVisit(BrowserHistory* obj, char* url);
char* browserHistoryBack(BrowserHistory* obj, int steps);
char* browserHistoryForward(BrowserHistory* obj, int steps);
void browserHistoryFree(BrowserHistory* obj);

#endif
