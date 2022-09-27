#include <iostream>
#include <vector>


#include "../include/vector.h"



int main(){

    Vector<int> v{1,2}, v2{3,4,5,6};



    v.push_back(20);
    std::cout << "Current size/ capacity: " << v.size() << " " << v.getCap() <<  "\n";
    for (auto i{0};  i < 1000; ++i)
    {
        v.push_back(20);
        std::cout << "Current size/ capacity: " << v.size() << " " << v.getCap() <<  "\n";
    }

    return 0;
}