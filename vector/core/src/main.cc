#include <iostream>
#include <vector>


#include "../include/vector.h"



int main(){

    Vector<int> v{1,2,3,4,5,6,7}, v2{3,4,5,6};


    v.resize(35);
    for (auto i{0};  i < v.size(); ++i)
    {
        std::cout << v[i] << " ";
    }

    return 0;
}