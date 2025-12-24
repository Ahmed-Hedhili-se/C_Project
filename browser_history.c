#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char **history;     
    int size;           
    int current_url;    
    int last_url;       
}BrowserHistory;

BrowserHistory* browserHistoryCreate(const char* homepage) {

    BrowserHistory* obj = (BrowserHistory*)malloc(sizeof(BrowserHistory));
    if (!obj) return NULL;  

    obj->size = 1000; 
    obj->history = (char**)malloc(obj->size * sizeof(char*));
    if (!obj->history) {
        free(obj);
        return NULL;
    }

    obj->history[0] = strdup(homepage);  
    obj->current_url = 0;
    obj->last_url = 0;

    return obj;
}
void browserHistoryVisit(BrowserHistory* obj, const char* url) {
    obj->current_url++;

    // resize if array is full
    if (obj->current_url >= obj->size) {
        obj->size *= 2;

        
        char **temp = (char**)realloc(obj->history, obj->size * sizeof(char*));
        if (!temp) {
            
            return;  
        }
        obj->history = temp;
    }
    obj->history[obj->current_url] = strdup(url);

    obj->last_url = obj->current_url;
}

char* browserHistoryBack(BrowserHistory* obj, int steps) {

    obj->current_url -= steps;
    if (obj->current_url < 0)
        obj->current_url = 0;

    return obj->history[obj->current_url];
}
char* browserHistoryForward(BrowserHistory* obj, int steps) {

    obj->current_url += steps;
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
