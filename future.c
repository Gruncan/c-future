
#include "future.h"

#include <pthread.h>
#include <stdlib.h>


struct sFuture {
    void* rValue;
    pthread_mutex_t _mutex;
    pthread_cond_t _mutex_cond;
    pthread_t _thread;
};

struct sFutureTarget {
    struct sFuture* future;
    void* (*func)(void*);
    void* args;
};


struct sFuture* new_future() {
    struct sFuture* future = malloc(sizeof(struct sFuture));
    future->rValue = NULL;
    pthread_mutex_init(&future->_mutex, NULL);
    pthread_cond_init(&future->_mutex_cond, NULL);

    return future;
}

void* get_future(Future* f) {
    if (f == NULL) return NULL;

    pthread_mutex_lock(&f->_mutex);
    while (f->rValue == NULL) {
        pthread_cond_wait(&f->_mutex_cond, &f->_mutex);
    }
    pthread_mutex_unlock(&f->_mutex);

    return f->rValue;
}

void set_future(Future* f, void* val) {
    pthread_mutex_lock(&f->_mutex);
    f->rValue = val;
    pthread_mutex_unlock(&f->_mutex);
    pthread_cond_signal(&f->_mutex_cond);

}

void del_future(Future* f) {
    pthread_cond_destroy(&f->_mutex_cond);
    pthread_mutex_destroy(&f->_mutex);
    free(f);
}

void* check_future(Future* f) {
    if (f == NULL) return NULL;

    return f->rValue;
}


void thread_runner(void* arg) {
    struct sFutureTarget* futureTarget = arg;
    void* rValue = futureTarget->func(futureTarget->args);

    set_future(futureTarget->future, rValue);

    free(futureTarget);
}


Future* async(void* (*func)(void*), void* args) {
    struct sFutureTarget* futureTarget = malloc(sizeof(struct sFutureTarget));
    futureTarget->func = func;
    futureTarget->args = args;

    struct sFuture* future = new_future();

    futureTarget->future = future;

    pthread_create(&future->_thread, NULL, thread_runner, futureTarget);

    return future;
}

