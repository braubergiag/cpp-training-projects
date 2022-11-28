//
// Created by igor on 28.11.22.
//

#include <utility>

#include "../include/book.h"
#include "../include/rapidcsv.h"
#include <string>




int Book::getCopyAmount() const {
    return copy_amount_;
}

void Book::setCopyAmount(int copyAmount) {
    copy_amount_ = copyAmount;
}

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

int Book::getCopyAvailable() const {
    return copy_available_;
}

void Book::setCopyAvailable(int copyAvailable) {
    copy_available_ = copyAvailable;
}

Book::Book(std::string author,
           std::string title,
           std::string isbn, int copyAmount) :
                 author_(std::move(author)), title_(std::move(title)),
                 isbn_(std::move(isbn)), copy_amount_(copyAmount),copy_available_(copyAmount){}

bool operator==(const Book &lhs, const Book &rhs) {
    return lhs.getIsbn() == rhs.getIsbn();
}

std::ostream &operator<<(std::ostream &os, const Book &book) {

    os  << "Title: " << book.getTitle() << "\n"
        << "Authors: " << book.getAuthor() << "\n"
        << "ISBN: " << book.getIsbn();
    return os;
}
