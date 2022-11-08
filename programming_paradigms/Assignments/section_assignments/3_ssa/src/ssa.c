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


    ssa->numGroups = arrayLength / groupSize;
    ssa->groups =  malloc(sizeof(group) *  ssa->numGroups);

    for (int i = 0; i <  ssa->numGroups; ++i){
        group * grp = (group * ) ((char *) ssa->groups + sizeof(group) * i);
        grp->bitmap = malloc(groupSize * sizeof(bool));
        VectorNew(&grp->strings,sizeof(char *), NULL,groupSize);

        for (int elemIndex = 0 ; elemIndex < ssa->groupSize; ++elemIndex){
            *( (char *) grp->bitmap + sizeof (bool) * elemIndex) = false;
//            grp->bitmap[*(int *)((char *) grp->bitmap + sizeof (bool) * elemIndex)] = false;
        }
    }





}

bool SSAInsert(sparsestringarray *ssa, int index, const char *str){

    int groupIndex =  index / ssa->groupSize;
    int elemIndex = index % ssa->groupSize;


    group * gr = (group *) ( (char *) ssa->groups + groupIndex * sizeof (group) );



    if (gr->bitmap[elemIndex] == true){

        int i = 0, position = 0;
        while (i++ < elemIndex) {
            if (gr->bitmap[i] == true) ++position;
        }
        VectorReplace(&gr->strings,str,position);
    } else {
        gr->bitmap[elemIndex] = true;
        VectorAppend(&gr->strings,str);
    }


}


void SSAMap(sparsestringarray *ssa, SSAMapFunction mapfn, void *auxData){
    for (int groupIndex = 0; groupIndex < ssa->numGroups;++groupIndex){

        group * gr = (group *) ( (char *) ssa->groups + groupIndex * sizeof (group) );
        int vectorIndex = 0;
        for (int elemIndex = 0; elemIndex < ssa->groupSize; elemIndex++){

            void * elemAddr;
            if (gr->bitmap[elemIndex] != false){
               elemAddr = VectorNth(&gr->strings,vectorIndex);
               vectorIndex++;
            } else {
                elemAddr = (char *) "";
            }
            mapfn(ssa->groupSize * groupIndex + elemIndex,elemAddr,auxData);

        }
    }
}

void SSADispose(sparsestringarray *ssa){

}