#ifndef FUTURE_H
#define FUTURE_H

typedef struct sFuture Future;

Future* async(void* func, void* arg);

void* get(Future*);

void del(Future*);

#endif //FUTURE_H
