//
// Created by igor on 08.11.22.
//

#ifndef ICU_PROJECT_SSA_H
#define ICU_PROJECT_SSA_H


#include "vector.h"
#include "bool.h"


typedef struct {
    bool *bitmap; // set to be of size 'groupSize'
    vector strings; // vector of dynamically allocated, nonempty C strings
} group;

typedef struct {
    group *groups; // dynamically allocated array of structs, defined below
    int numGroups; // number of groups
    int arrayLength; // logical length of the full sparsestringarray
    int groupSize; // number of strings managed by each group
} sparsestringarray;


/**
 * Function: SSANew
 * ----------------
 * Constructs the sparsestringarray addressed by the first argument to
 * be of the specified length, using the specified group size to decide
 * how many groups should be used to back the implementation. You can
 * assume that arrayLength is greater than groupSize, and for simplicity you
 * can also assume that groupSize divides evenly into arrayLength.
 */
void SSANew(sparsestringarray *ssa, int arrayLength, int groupSize);
/**
 * Function: SSADispose
 * --------------------
 * Disposes of all the resources embedded within the addressed
 * sparsestringarray that have built up over the course of its
 * lifetime.
 */
void SSADispose(sparsestringarray *ssa);
/**
 * Function: SSAInsert
 * -------------------
 * Inserts the C string addressed by str into the sparsestringarray addressed
 * by ssa at the specified index. If some nonempty string already resides
 * at the specified index, then it is replaced with the new one. Note that
 * SSAInsert makes a deep copy of the string address by str.
 */
bool SSAInsert(sparsestringarray *ssa, int index, const char *str);
/**
 * Function: SSAMap
 * ----------------
 * Applies the specified mapping routine to every single index/string pair
 * (along with the specified auxiliary data). Note that the mapping routine
 * is called on behalf of all strings, both empty and nonempty.
 */
typedef void (*SSAMapFunction)(int index, const char *str, void *auxData);
void SSAMap(sparsestringarray *ssa, SSAMapFunction mapfn, void *auxData);
#endif //ICU_PROJECT_SSA_H
