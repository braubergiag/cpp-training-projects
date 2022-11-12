#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void  swap(void * pa, void *pb, size_t elemSize) {

    void * temp = malloc(elemSize);
    memcpy(temp,pa,elemSize);
    memcpy(pa,pb,elemSize);
    memcpy(pb,temp,elemSize);
    free(temp);


}

void swap_lec(void * vp1, void * vp2, int size){

    char buffer[size];
    memcpy(buffer,vp1,size);
    memcpy(vp1,vp2,size);
    memcpy(vp2,buffer,size);

}

int main(){


    int a = 5;
    int * pa = &a;
    int b = 44;

    char * husband = strdup("Frederuc Begbeder");
    char * wife = strdup("Wilma Wittaker");

    swap_lec(&husband,&wife, sizeof(char *));


}