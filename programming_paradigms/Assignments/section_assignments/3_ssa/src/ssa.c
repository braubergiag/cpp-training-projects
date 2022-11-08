//
// Created by igor on 08.11.22.
//
#include <malloc.h>
#include "../include/ssa.h"


void StringFreeFn(void * elemAddr){
    free(*(char **) elemAddr);
}


void SSANew(sparsestringarray *ssa, int arrayLength, int groupSize){

    ssa->arrayLength = arrayLength;
    ssa->groupSize = groupSize;


    int numberOfGroups = arrayLength / groupSize;

    ssa->groups =  malloc(sizeof(group) * numberOfGroups);

    for (int i = 0; i < numberOfGroups; ++i){
        group * grp = (group * ) ((char *) ssa->groups + sizeof(group) * i);
        grp->bitmap = malloc(groupSize);
        VectorNew(&grp->strings,sizeof(char *), StringFreeFn,groupSize);
    }



}