#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/ssa.h"
//
// Created by igor on 08.11.22.
//


void StringFree(void * elem){
    printf("(char **) elem %p\n",(char **) elem);
    printf("*(char **) elem %p\n",*(char **) elem);

    free(*(char **) elem);
}

static void CountEmptyPrintNonEmpty(int index, const char *str, void *auxData)
{
    if (strcmp(str, "") != 0) {
        printf("Oooo! Nonempty string at index %d: \"%s\"\n", index, str);
    } else {
        (*(int *)auxData)++;
    }
}




int main(){


    sparsestringarray ssa;
    printf("%lu\n", sizeof(bool));
    SSANew(&ssa, 70000, 35);
    SSAInsert(&ssa, 33001, "need");
    SSAInsert(&ssa, 58291, "more");
//    SSAInsert(&ssa, 32993, "Aba");
//    SSAInsert(&ssa, 32998, "Ava");
//    SSAInsert(&ssa, 32993, "A");
    SSAInsert(&ssa, 32996, "Awq");
    SSAInsert(&ssa, 32995, "Are");
    SSAInsert(&ssa, 32995, "Who we Are");
    SSAInsert(&ssa, 32997, "At");
    SSAInsert(&ssa, 32997, "At home");
    SSAInsert(&ssa, 33000, "Eye");
    SSAInsert(&ssa, 33000, "I");
    SSAInsert(&ssa, 67899, "cowbell");
    int numEmptyStrings = 0;
    SSAMap(&ssa, CountEmptyPrintNonEmpty, &numEmptyStrings);
    printf("%d of the strings were empty strings.\n", numEmptyStrings);
//    SSADispose(&ssa);



}