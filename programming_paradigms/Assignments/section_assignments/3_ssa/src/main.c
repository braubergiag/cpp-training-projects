#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/ssa.h"
//
// Created by igor on 08.11.22.
//


void StringFree(void * elem){
    printf("(char **) elem %p\n",(char **) elem);
    printf("*(char **) elem %p\n",*(char **) elem);

    free(*(char **) elem);
}
int main(){


    vector  v;
    VectorNew(&v,sizeof(char *), StringFree,10);

    char * copy = strdup("Will");
    printf("&copy %p\n", &copy);
    printf("copy %p\n", copy);
    VectorAppend(&v,&copy);

    VectorDispose(&v);


}