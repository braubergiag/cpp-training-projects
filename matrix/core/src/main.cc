#include <iostream>



#include "../include/matrix.h"


int main(){

    Matrix<int> m(10,20);
    m.fill_zeros();
    m.print();



    return 0;
}