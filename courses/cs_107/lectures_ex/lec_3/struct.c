#include <stdio.h>

struct fraction {


    int num;
    int denum;


};







int main(){

    struct fraction pi;
    pi.num = 22;
    pi.denum = 7;

    // ((struct fraction *) & (pi.denum))->num = 12;  
    // ((struct fraction *) & (pi.denum))->denum = 23;  


    // int arr[5];
    // arr[3] = 128;
    // ((short *) arr)[7] = 2;
    // printf("%i\n", arr[3]);
    // printf("%li\n", sizeof(short));
    // printf("%li\n", sizeof(int));
    // printf("%li\n", sizeof(char));
    // arr[1] = 128;
    // ((short *) ((char *)(&arr[0]) + 4))[1] = 2;
    //  printf("%i\n", arr[1]);
    printf("%p\n", &pi);
    printf("%p\n", &pi.num);
    printf("%p\n", &pi.denum);

}