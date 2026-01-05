#ifndef BROWSER_HISTORY_H
#define BROWSER_HISTORY_H

typedef struct BrowserHistory BrowserHistory; 

BrowserHistory* browserHistoryCreate(const char* homepage); 
void browserHistoryVisit(BrowserHistory* obj, const char* url); 
char* browserHistoryBack(BrowserHistory* obj, int steps);
char* browserHistoryForward(BrowserHistory* obj, int steps);
void browserHistoryFree(BrowserHistory* obj);

#endif
