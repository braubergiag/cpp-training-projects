//
// Created by igor on 28.11.22.
//

#ifndef LIBRARY_LIBRARY_H
#define LIBRARY_LIBRARY_H

#include "book.h"
#include "patron.h"
#include <vector>

struct BookInfo {
    Book book;
    int copy_amount;
    int copy_available;

};

struct Transaction {
    Patron patron;
    Book book;

};
class library {

public:
    void read_from_file();


private:
    std::vector<BookInfo> books_;
    std::vector<Patron> patrons_;
    std::vector<Transaction> transactions_;
};


#endif //LIBRARY_LIBRARY_H
