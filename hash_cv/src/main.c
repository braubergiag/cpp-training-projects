
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


int main()
{



    TEST_HashSetNew();
//    TEST_VectorNew();
    return 0;
}