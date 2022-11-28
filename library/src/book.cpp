//
// Created by igor on 28.11.22.
//

#include <utility>

#include "../include/book.h"
#include "../include/rapidcsv.h"
#include <string>


const std::string &Book::getTitle() const {
    return title_;
}

void Book::setTitle(const std::string &title) {
    title_ = title;
}

const std::string &Book::getAuthor() const {
    return author_;
}

void Book::setAuthor(const std::string &author) {
    author_ = author;
}

const std::string &Book::getIsbn() const {
    return isbn_;
}

void Book::setIsbn(const std::string &isbn) {
    isbn_ = isbn;
}

Book::Book(std::string author,
           std::string title,
           std::string isbn, int copyAmount) :
                 author_(std::move(author)), title_(std::move(title)),
                 isbn_(std::move(isbn)){}

bool operator==(const Book &lhs, const Book &rhs) {
    return lhs.getIsbn() == rhs.getIsbn();
}

std::ostream &operator<<(std::ostream &os, const Book &book) {

    os  << "Title: " << book.getTitle() << "\n"
        << "Authors: " << book.getAuthor() << "\n"
        << "ISBN: " << book.getIsbn();
    return os;
}
