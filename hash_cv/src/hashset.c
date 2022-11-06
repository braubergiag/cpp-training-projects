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
    h->compareFn = comparefn;
    h->hashFn = hashfn;
    if (freefn != NULL) {
        h->freeFn = freefn;
    }


}

void HashSetDispose(hashset *h)
{}

int HashSetCount(const hashset *h)
{ return 0; }

void HashSetMap(hashset *h, HashSetMapFunction mapfn, void *auxData)
{}

void HashSetEnter(hashset *h, const void *elemAddr)
{}

void *HashSetLookup(const hashset *h, const void *elemAddr)
{ return NULL; }
