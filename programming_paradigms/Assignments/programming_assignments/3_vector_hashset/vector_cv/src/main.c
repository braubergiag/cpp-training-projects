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

void Test_Vector_Replace(vector * v){
    VectorNew(v,sizeof(int),NULL,10);
    int num = 2, num2 = 30, num3 = 40;
    VectorAppend(v,&num);


    VectorReplace(v,&num3,0);
    int * target_3 = VectorNth(v,0);
    assert(*target_3 == num3);

}

void Test_Vector_Insert(){
    vector v;
    VectorNew(&v,sizeof(int),NULL,10);
    int num1 = 2, num2 = 30, num3 = 40;
    VectorAppend(&v,&num1);
    VectorAppend(&v,&num2);
    VectorAppend(&v,&num3);

    int num4 = 44;
    VectorInsert(&v,&num4,0);

    int * target_1 = VectorNth(&v,0);
    int * target_2 = VectorNth(&v,1);
    int * target_3 = VectorNth(&v,2);
    int * target_4 = VectorNth(&v,3);
    assert(*target_1 == num4);
    assert(*target_2 == num1);
    assert(*target_3 == num2);
    assert(*target_4 == num3);

    VectorDispose(&v);

}

void Test_Vector_Delete(){
    {

        vector v;
        VectorNew(&v,sizeof(int),NULL,10);
        int num1 = 2, num2 = 30, num3 = 40;
        VectorAppend(&v,&num1);
        VectorAppend(&v,&num2);
        VectorAppend(&v,&num3);

        VectorDelete(&v,0);

        int * target_2 = VectorNth(&v,0);
        int * target_3 = VectorNth(&v,1);
        assert(*target_2 == num2);
        assert(*target_3 == num3);
        VectorDispose(&v);

    }
    {

        vector v;
        VectorNew(&v,sizeof(int),NULL,10);
        for (int i = 0; i < 10; ++i){
            VectorAppend(&v,&i);
        }
        assert(v.logLen == 10);
        for (int i = 0; i < 9; ++i){
            VectorDelete(&v,0);
            int * t = VectorNth(&v,0);
            assert(*t == i + 1);
        }

        VectorDispose(&v);

    }
    {

        vector v;
        VectorNew(&v,sizeof(int),NULL,10);
        for (int i = 0; i < 10; ++i){
            VectorAppend(&v,&i);
        }
        assert(v.logLen == 10);
        for (int i = 9; i > 0; --i){
            VectorDelete(&v,i);
            int * t = VectorNth(&v,i-1);
            assert(*t == i - 1);
        }

        VectorDispose(&v);

    }
    {

    }

}

void Test_Vector_Grow(){

    vector v;
    VectorNew(&v,sizeof(int),NULL,2);
    int num1 = 2, num2 = 30, num3 = 40;
    VectorAppend(&v,&num1);
    VectorAppend(&v,&num2);
    VectorAppend(&v,&num3);
    assert(v.allocLen == 4);

}


int main(){

    vector v;
//    Test_Vector_New(&v);
    Test_Vector_Replace(&v);
    Test_Vector_Insert();
    Test_Vector_Delete();
    Test_Vector_Grow();



}