#include "../include/hashset.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

void HashSetNew(hashset *h, int elemSize, int numBuckets,
		HashSetHashFunction hashfn, HashSetCompareFunction comparefn, HashSetFreeFunction freefn)
{


    assert(elemSize > 0 && numBuckets > 0 && hashfn != NULL && comparefn != NULL);

    h->elemSize = elemSize;
    h->numberOfBuckets = numBuckets;
    h->numberOfElements = 0;
    VectorNew(&h->buckets,sizeof (vector),NULL,h->numberOfBuckets);
    for (int i = 0; i < h->numberOfBuckets; ++i){
        vector v;
        VectorNew(&v,h->elemSize,NULL,10);
        VectorAppend(&h->buckets,&v);

    }
    h->compareFn = comparefn;
    h->hashFn = hashfn;
    if (freefn != NULL) {
        h->freeFn = freefn;
    }


}

void HashSetDispose(hashset *h)
{
    for (int i = 0; i < h->numberOfBuckets; ++i){
        VectorDispose(VectorNth(&h->buckets,i));
    }

    VectorDispose(&h->buckets);
}

int HashSetCount(const hashset *h)
{ return h->numberOfElements; }

void HashSetMap(hashset *h, HashSetMapFunction mapfn, void *auxData)
{

    for (int i = 0; i < h->numberOfBuckets; ++i){

    }


}

void HashSetEnter(hashset *h, const void *elemAddr)
{

    int bucket = h->hashFn(elemAddr,h->numberOfBuckets);

    vector * v = VectorNth(&h->buckets, bucket);

    int index = VectorSearch(v,elemAddr,h->compareFn,0,false);
    if (index != -1) {
        VectorReplace(v,elemAddr,index);
    } else {
        VectorAppend(v,elemAddr);
        h->numberOfElements++;
    }





}

void *HashSetLookup(const hashset *h, const void *elemAddr)
{

    for (int i = 0; i < h->numberOfBuckets; ++i){
        int bucket = h->hashFn(elemAddr,h->numberOfBuckets);
        vector * v = VectorNth(&h->buckets, bucket);
        int index = VectorSearch(v,elemAddr,h->compareFn,0,false);
        if (index != -1){
            return VectorNth(v, index);
        }
    }

    return NULL;
}
