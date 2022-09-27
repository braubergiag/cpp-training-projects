#include <iostream>
#include <vector>


#include "../include/vector.h"



int main(){

    Vector<int> v;



    v.push_back(20);
    for (auto i{0};  i < 1000; ++i)
    {
        v.push_back(20);
        std::cout << "Current size/ capacity: " << v.size() << " "  <<  "\n";
    }

    return 0;
}