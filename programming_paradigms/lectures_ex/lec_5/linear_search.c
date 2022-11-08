#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>





void * linear_search(void * base, void * key, int n, int elemSize, int (*cmpfn)(void *, void *)){

    for (int i = 0; i < n; ++i){
        void * elemAddr = (char *) base + i * elemSize;


        if (cmpfn(elemAddr,key) == 0) {
            return elemAddr;
        }
    }

    return NULL;

}


int main(){


    char * notes[] = {"Ab","F#","B","Gb","D"};

    

}