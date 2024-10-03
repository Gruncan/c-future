
#include "future.h"

#include <pthread.h>
#include <stdlib.h>


struct sFuture {
    void* rValue;
    pthread_mutex_t mutex;
    pthread_cond_t mutex_cond;
    pthread_t thread;
};


Future* async(void* func, void* arg) {
    // TODO this needs to wrap around the function more to handle return type correctly
    struct sFuture* fut = malloc(sizeof(struct sFuture));
    pthread_mutex_init(&fut->mutex, NULL);
    pthread_cond_init(&fut->mutex_cond, NULL);
    pthread_create(&fut->thread, NULL, func, arg);

    return fut;
}

void* get(Future*) {
    // TODO wait until the condt had been changed
}

void del(Future* fut) {
    if(fut != NULL) {
        free(fut);
    }
}
