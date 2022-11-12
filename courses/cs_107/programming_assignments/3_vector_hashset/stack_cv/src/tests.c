

#include "../include/tests.h"
#include "../include/stack.h"
#include <assert.h>
#include <stddef.h>


void TEST_STACK_NEW(){

    stack s;

    const int initialSize = 10;
    int test_size = 20000;
    StackNew(&s,sizeof(int),NULL, initialSize);



    for (int i = 0; i < test_size; ++i){
        StackPush(&s,&i);

    }

    int num;
    for (int i = 0; i < test_size; ++i){
        StackPop(&s,&num);
        assert(num == (test_size - (i + 1)));
    }


    StackDispose(&s);

}
