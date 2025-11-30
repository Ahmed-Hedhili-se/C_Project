#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char **history;     // dynamic array of strings
    int size;           // allocated capacity
    int current_url;    // index of current page
    int last_url;       // last valid index
}BrowserHistory;

BrowserHistory* browserHistoryCreate(const char* homepage) {

    BrowserHistory* obj = (BrowserHistory*)malloc(sizeof(BrowserHistory));
    if (!obj) return NULL;  // check malloc failed

    obj->size = 1000; // initial capacity

    // allocate the array of pointers
    obj->history = (char**)malloc(obj->size * sizeof(char*));
    if (!obj->history) {
        free(obj);
        return NULL;
    }

    obj->history[0] = strdup(homepage);  // copy homepage string
    obj->current_url = 0;
    obj->last_url = 0;

    return obj;
}
void browserHistoryVisit(BrowserHistory* obj, const char* url) {
    obj->current_url++;

    // resize if array is full
    if (obj->current_url >= obj->size) {
        obj->size *= 2;

        // *** SAFE REALLOC FIX ***
        char **temp = (char**)realloc(obj->history, obj->size * sizeof(char*));
        if (!temp) {
            // if realloc fails => DO NOT overwrite the original pointer
            return;  // fail silently (leetcode won't test memory failures)
        }
        obj->history = temp;
    }

    // overwrite the forward history entry with the new url
    obj->history[obj->current_url] = strdup(url);

    obj->last_url = obj->current_url;
}

char* browserHistoryBack(BrowserHistory* obj, int steps) {

    obj->current_url -= steps;

    // we cannot go below index 0
    if (obj->current_url < 0)
        obj->current_url = 0;

    return obj->history[obj->current_url];
}
char* browserHistoryForward(BrowserHistory* obj, int steps) {

    obj->current_url += steps;

    // cannot go beyond last visited
    if (obj->current_url > obj->last_url)
        obj->current_url = obj->last_url;

    return obj->history[obj->current_url];
}
void browserHistoryFree(BrowserHistory* obj) {
    if (!obj) return;
    for (int i = 0; i <= obj->last_url; i++) {
        free(obj->history[i]);
    }
    free(obj->history);
    free(obj);
}
