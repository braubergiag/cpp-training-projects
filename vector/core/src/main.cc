#include <iostream>
#include <vector>


#include "../include/vector.h"



int main(){

    const Vector<int> v{1,2,3,4};
    const std::vector<int> vv{1,2,3,4};



    std::cout << v.front();
    return 0;
}