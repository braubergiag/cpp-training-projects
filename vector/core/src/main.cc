#include <iostream>



#include "../include/vector.h"



int main(){

    Vector<int> vec{2,3,5,6};

    for (auto i{0}; i < vec.size(); ++i)
    {
        std::cout << vec[i] << " ";
    }    
    std::cout << "\n";
    Vector<int> vec_2(10,30);

    for (auto i{0}; i < vec.size(); ++i)
    {
        std::cout << vec_2[i] << " ";
    }    
    return 0;
}