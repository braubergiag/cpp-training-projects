#include <iostream>
#include <vector>


#include "../include/vector.h"



int main(){

    Vector<int> v{1,2,3,4}, v2{3,4,5,6};

    v2=  v;
    return 0;
}