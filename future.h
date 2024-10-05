#ifndef FUTURE_H
#define FUTURE_H

typedef struct sFuture Future;

Future* async(void* (*func)(void*), void* args);

Future* new_future();

void del_future(Future* f);

void* get_future(Future* f);

void set_future(Future* f, void* val);

void* check_future(Future* f);

#endif //FUTURE_H
