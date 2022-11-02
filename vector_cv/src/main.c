#include "../include/vector.h"
#include <stddef.h>
#include <assert.h>

void Test_Vector_New(vector * v){
    VectorNew(v,sizeof(int),NULL,10);
    int num = 2, num2 = 30, num3 = 40;
    VectorAppend(v,&num);
    VectorAppend(v,&num2);
    VectorAppend(v,&num3);

    int * target_1 = VectorNth(v,0);
    int * target_2 = VectorNth(v,1);
    int * target_3 = VectorNth(v,2);
    assert(*target_1 == num);
    assert(*target_2 == num2);
    assert(*target_3 == num3);
}



int main(){

    vector friends;



}