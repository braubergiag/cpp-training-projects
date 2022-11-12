#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/ssa.h"

void StringFree(void * elem){
    printf("(char **) elem %p\n",(char **) elem);
    printf("*(char **) elem %p\n",*(char **) elem);

    free(*(char **) elem);
}

static void CountEmptyPrintNonEmpty(int index, const char *str, void *auxData)
{
    if (strcmp(str, "") != 0) {
        printf("Oooo! Nonempty string at index %d: \"%s\"\n", index, str);
    } else {
        (*(int *)auxData)++;
    }
}




void TEST_SSAInsert(){
    sparsestringarray ssa;
    printf("%lu\n", sizeof(bool));
    SSANew(&ssa, 100000, 10);
    SSAInsert(&ssa, 1, "need");
    SSAInsert(&ssa, 1, "more");
    SSAInsert(&ssa, 1, "bank");
    SSAInsert(&ssa, 1, "trust");
    SSAInsert(&ssa, 1, "safety");
    SSAInsert(&ssa, 2, "safety");
    SSAInsert(&ssa, 10, "safety");
    SSAInsert(&ssa, 3, "house");
    SSAInsert(&ssa, 4, "code");
    int numEmptyStrings = 0;
    SSAMap(&ssa, CountEmptyPrintNonEmpty, &numEmptyStrings);
    printf("%d of the strings were empty strings.\n", numEmptyStrings);
    SSADispose(&ssa);

}

void TEST_VectorInsert(){


    vector v;
    VectorNew(&v,sizeof(char *),StringFree,10);



    char * str1 = strdup("House");
    char * str2 = strdup("bookstore");
    VectorAppend(&v,&str1);
    VectorAppend(&v,&str2);


    for (int i = 0; i < v.logLen; ++i){
        char * str = VectorNth(&v,i);
        printf("%s\n",*(char ** ) str);
    }
}


void swap(void * vp1, void * vp2, int elemSize){

    char buffer[elemSize];

    memcpy(buffer,vp1,elemSize);
    memcpy(vp1,vp2,elemSize);
    memcpy(vp2,buffer,elemSize);

}


int main(){


    TEST_SSAInsert();


}