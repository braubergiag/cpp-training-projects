#include "../include/stack.h"
#include <assert.h>
#include <malloc.h>
#include <memory.h>


void StackNew(stack * s,  int elemSize,StackFreeFunction freeFunc,int initialSize){

    assert(initialSize > 0);
    assert(elemSize > 0);
    s->elemSize = elemSize;
    s->logLength = 0;
    s->allocLength = initialSize;
    if (freeFunc != NULL) s->freeFunction = freeFunc;
    s->elems = malloc(elemSize * initialSize);
}
void StackDispose(stack *s){

    if (s->freeFunction != NULL){
        for (int i = 0; i < s->logLength; ++i){
            void * target = (char *) s->elems + i * s->elemSize;
            s->freeFunction(target);
        }
    }

    free(s->elems);

}
void StackPush(stack * s, void * elemAddr){

    if (s->logLength == s->allocLength) {
        StackGrow(s);
    }
    void * target = (char *) s->elems  + s->logLength * s->elemSize;
    memcpy(target,elemAddr,s->elemSize);
    s->logLength++;
}
void StackPop(stack *s, void * elemAddr){

    s->logLength--;
    void * target = (char *) s->elems + s->elemSize * s->logLength;
    memcpy(elemAddr,target,s->elemSize);

}

static void StackGrow(stack * s){

    s->allocLength *= 2;
    s->elems = realloc(s->elems, s->allocLength * s->elemSize);
    assert(s->elems != NULL);

}