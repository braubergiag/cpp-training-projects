//
// Created by igor on 28.11.22.
//

#ifndef LIBRARY_PATRON_H
#define LIBRARY_PATRON_H


#include "book.h"
#include <vector>
#include <string>
class Patron { ;
public:
    Patron(std::string name, int card_number) : name_(std::move(name)), card_number_(card_number) {}




public:
    void borrow_book(const Book & book);
    void return_book(const Book &book);



public:
    const std::string &get_name() const;
    int get_card_number() const;
    const std::vector<Book> &get_books() const;



private:
    std::string name_;
    int card_number_;
    std::vector<Book> books_;

};


#endif //LIBRARY_PATRON_H
