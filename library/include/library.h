//
// Created by igor on 28.11.22.
//

#ifndef LIBRARY_LIBRARY_H
#define LIBRARY_LIBRARY_H

#include "book.h"
#include "patron.h"
#include <vector>
class library {

public:
    void read_from_file();


private:
    std::vector<Book> books_;
    std::vector<Patron> patrons_;
};


#endif //LIBRARY_LIBRARY_H
