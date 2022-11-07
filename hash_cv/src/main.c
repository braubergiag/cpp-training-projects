
#include <memory.h>
#include <assert.h>
#include "../include/hashset.h"

int hash_number(const void * num, int numBuckets) {
   return (*(int *) num ) % numBuckets;
}

int hash_compare(const void * num_1, const void * num_2){
    return memcmp(num_1,num_2,sizeof (int));
}
void TEST_HashSetNew(){

    hashset h;

    HashSetNew(&h,sizeof(int),3, hash_number, hash_compare,NULL);
    assert(h.elemSize == sizeof(int));
    assert(h.numberOfBuckets == 3);
    assert(h.hashFn == &hash_number);
    assert(h.compareFn == &hash_compare);


    HashSetDispose(&h);
}


void TEST_VectorNew(){


    vector  v;
    VectorNew(&v,sizeof(vector), VectorDispose, 3);

    vector a;
    VectorNew(&a,sizeof(int),NULL, 10);
    VectorAppend(&v,&a);


    VectorDispose(&v);


}

void TEST_HashSetEnter(){

    hashset h;

    HashSetNew(&h,sizeof(int),10, hash_number, hash_compare,NULL);
    for (int i = 0; i < 100; ++i){
        HashSetEnter(&h,&i);
    }
    assert(h.numberOfElements == 100);

    for (int i = 0; i < 100; ++i){
        HashSetEnter(&h,&i);
    }
    assert(h.numberOfElements == 100);



    HashSetDispose(&h);


}

void TEST_HashSetLookUp(){
    hashset h;

    HashSetNew(&h,sizeof(int),10, hash_number, hash_compare,NULL);
    for (int i = 0; i < 100; ++i){
        HashSetEnter(&h,&i);
    }
    assert(h.numberOfElements == 100);

    for (int i = 0; i < 100; ++i) {

        int * res = HashSetLookup(&h,&i);
        assert(res != NULL);

    }


    HashSetDispose(&h);
}



int main()
{



    TEST_HashSetNew();
//    TEST_VectorNew();
TEST_HashSetEnter();
TEST_HashSetLookUp();
    return 0;
}