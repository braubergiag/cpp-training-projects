//
// Created by igor on 28.11.22.
//

#ifndef LIBRARY_PATRON_H
#define LIBRARY_PATRON_H


#include "book.h"
#include <vector>
#include <string>
class Patron {
    Patron(std::string name) : name_(std::move(name)) {};

    std::string name_;
    std::vector<Book> books_;
};


#endif //LIBRARY_PATRON_H
