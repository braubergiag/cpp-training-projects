#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation)
{
    v->allocationSize = 10;

    assert(initialAllocation > 0);
    v->logLen = 0;
    v->elemSize = elemSize;

    if (initialAllocation == 0) initialAllocation = v->allocationSize;
    v->allocLen = initialAllocation;
    v->elems = malloc(v->elemSize * v->allocLen);
    v->freeFn = freeFn;

}

void VectorDispose(vector *v)
{
    if (v->freeFn != NULL){
        for (int i = 0; i < v->logLen; ++i){
            v->freeFn(v->elems + v->elemSize * i);
        }
    }
    free(v->elems);

}

int VectorLength(const vector *v)
{ return v->logLen; }

void *VectorNth(const vector *v, int position)
{
    assert(position >= 0 && position < v->logLen);
    void * target = v->elems + v->elemSize * position;
    return target;


}

void VectorReplace(vector *v, const void *elemAddr, int position)
{}

void VectorInsert(vector *v, const void *elemAddr, int position)
{}

void VectorAppend(vector *v, const void *elemAddr)
{

    void * target = (char *) v->elems + v->logLen * v->elemSize;
    memcpy(target,elemAddr,v->elemSize);
    v->logLen++;

}

void VectorDelete(vector *v, int position)
{}

void VectorSort(vector *v, VectorCompareFunction compare)
{}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData)
{}

static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted)
{ return -1; } 
