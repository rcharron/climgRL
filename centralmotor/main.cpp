#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <functional>
#include "estimator.h"


 
void (*ctest1)(int *);
void (*ctest2)(int *);
 
 
int main(){
    void *handle;
    char *error;
    int x, y, z;
 
    handle = dlopen ("libctest.so.1", RTLD_LAZY);
    if (!handle) {
        fputs (dlerror(), stderr);
        exit(1);
    }
 
    ctest1 = (void(*)(int*) )( dlsym(handle, "ctest1"));
    if (( error = dlerror() ) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }
 
    ctest2 = (void(*)(int*))(dlsym(handle, "ctest2"));
    if (( error = dlerror() ) != NULL)  {
        fputs(error, stderr);
        exit(1);
    }
 
    ctest1(&x);
    ctest2(&y);
    z = (x / y);
    printf("%d / %d = %d\n", x, y, z);
    dlclose(handle);
    return 0;
}
