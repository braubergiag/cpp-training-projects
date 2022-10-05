#include <iostream>



#include "../include/matrix.h"


int main(){

    Matrix<int> *  m = new Matrix<int>(10,20);
    m->fill_zeros();
    m->print();

    Matrix<int> * eye = Matrix<int>::eye(5);
    eye->print();
    delete m;
    delete eye;



    return 0;
}