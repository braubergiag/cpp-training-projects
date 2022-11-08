#include "../include/vector.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


const int DEFAULT_ALLOC_SIZE = 10;

static void VectorGrow(vector * v){
    v->allocLen += v->allocationSize;
    v->elems  = realloc(v->elems, v->allocLen * v->elemSize);
    assert(v->elems != NULL);
}


void VectorNew(vector *v, int elemSize, VectorFreeFunction freeFn, int initialAllocation)
{


    assert(initialAllocation > 0);
    v->logLen = 0;
    v->elemSize = elemSize;

    if (initialAllocation == 0){
        v->elems = malloc(v->elemSize * DEFAULT_ALLOC_SIZE);
        v->allocLen = DEFAULT_ALLOC_SIZE;
        v->allocationSize = DEFAULT_ALLOC_SIZE;
    } else {
        v->elems = malloc(v->elemSize * initialAllocation);
        v->allocLen = initialAllocation;
        v->allocationSize = initialAllocation;
    }

    v->allocLen = initialAllocation;
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
{
    assert(position >= 0 && position < v->logLen);
    void * target = (char *) v->elems + v->elemSize * position;
    if (v->freeFn != NULL) v->freeFn(target);
    memcpy(target,elemAddr,v->elemSize);

}

void VectorInsert(vector *v, const void *elemAddr, int position)
{
    assert(position >= 0 && position <= v->logLen);
    if (v->logLen == v->allocLen) {
        VectorGrow(v);
    }
    if (position == v->logLen) {
        VectorAppend(v,elemAddr);
        return;
    }
    int copy_size = (v->logLen - position) * v->elemSize;
    char buffer[copy_size];
    memcpy(buffer,v->elems + position, copy_size);
    memcpy(v->elems + position + v->elemSize,buffer,copy_size);

    void * target = v->elems + position * v->elemSize;
    memcpy(target,elemAddr,v->elemSize);

    v->logLen++;
}

void VectorAppend(vector *v, const void *elemAddr)
{

    if (v->logLen == v->allocLen) {
        VectorGrow(v);
    }
    void * target = v->elems + v->logLen * v->elemSize;
    memcpy(target,elemAddr,v->elemSize);
    v->logLen++;

}

void VectorDelete(vector *v, int position)
{
    assert(position >= 0 && position < v->logLen);

    void * target = (char *) v->elems + position * v->elemSize;
    if (v->freeFn != NULL) {
        v->freeFn(target);
    }

    int copy_size = (v->logLen - (position + 1)) * v->elemSize;
    char buffer[copy_size];
    memcpy(buffer,(char *) v->elems + (position + 1) * v->elemSize,copy_size);
    memcpy((char *) v->elems + position * v->elemSize,buffer, copy_size);
    v->logLen--;



}

void VectorSort(vector *v, VectorCompareFunction compare)
{


    qsort(v->elems,v->logLen,v->elemSize,compare);

}

void VectorMap(vector *v, VectorMapFunction mapFn, void *auxData)
{

    assert(mapFn != NULL);
    for (int i = 0; i < v->logLen; ++i){
        mapFn((char *) v->elems + i * v->elemSize, auxData);
    }

}

static const int kNotFound = -1;
int VectorSearch(const vector *v, const void *key, VectorCompareFunction searchFn, int startIndex, bool isSorted)
{
    assert(startIndex >= 0 && startIndex < v->logLen);
    assert(key != NULL);
    assert(searchFn != NULL);

    for (int i = startIndex; i < v->logLen; ++i) {
        if (searchFn(key, (char *) v->elems + v->elemSize * i) == 0) {
            return i;
        }
    }

    return -1; }
