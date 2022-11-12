//
// Created by igor on 12.11.22.
//

#ifndef ICU_PROJECT_STACK_H
#define ICU_PROJECT_STACK_H


typedef void (*StackFreeFunction)(void * elemAddr);

typedef struct {
    int elemSize;

    int logLength;
    int allocLength;
    StackFreeFunction freeFunction;
    void * elems;


} stack;

void StackNew(stack * s,  int elemSize,StackFreeFunction func,int initialSize);
void StackDispose(stack *s);
void StackPush(stack * s, void * elemAddr);
void StackPop(stack *s, void * elemAddr);

static void StackGrow(stack * s);

#endif //ICU_PROJECT_STACK_H
