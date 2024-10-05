

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "future.h"



int* test() {
    int a = 10;
    int b = 20;
    int* myInt = malloc(sizeof(int));
    *myInt = a+b;
    sleep(5);
    return myInt;
}




int main() {
    Future* f = async(test, NULL);

    printf("Check 1: %p\n", check_future(f));
    sleep(1);
    printf("Check 2: %p\n", check_future(f));
    sleep(1);

    int* v = get_future(f);
    printf("Address %p\n", v);
    printf("Got %d\n", *v);
    del_future(f);
    free(v);
}
