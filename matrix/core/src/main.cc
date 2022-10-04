#include <iostream>



#include "../include/matrix.h"


int main(){

    Matrix<int> *  m = new Matrix<int>(10,20);
    m->fill_zeros();
    m->print();

    
    delete m;



    return 0;
}