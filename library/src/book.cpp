//
// Created by igor on 28.11.22.
//

#include <utility>

#include "../include/book.h"
#include "../include/rapidcsv.h"
#include <string>


const std::string &Book::get_title() const {
    return title_;
}

void Book::set_title(const std::string &title) {
    title_ = title;
}

const std::string &Book::get_author() const {
    return author_;
}

void Book::set_author(const std::string &author) {
    author_ = author;
}

const std::string &Book::get_isbn() const {
    return isbn_;
}

void Book::set_isbn(const std::string &isbn) {
    isbn_ = isbn;
}

Book::Book(std::string author,
           std::string title,
           std::string isbn) :
                 author_(std::move(author)), title_(std::move(title)),
                 isbn_(std::move(isbn)){}

bool operator==(const Book &lhs, const Book &rhs) {
    return lhs.get_isbn() == rhs.get_isbn();
}

std::ostream &operator<<(std::ostream &os, const Book &book) {

    os << "Title: " << book.get_title() << "\n"
       << "Authors: " << book.get_author() << "\n"
        << "ISBN: " << book.get_isbn() << "\n";
    return os;
}
