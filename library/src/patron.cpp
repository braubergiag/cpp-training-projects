
#include "../include/patron.h"
#include <algorithm>

const std::string &Patron::get_name() const {
    return name_;
}

int Patron::get_card_number() const {
    return card_number_;
}

const std::vector<Book> &Patron::get_books() const {
    return books_;
}

void Patron::borrow_book(const Book &book) {
    books_.emplace_back(book);

}

void Patron::return_book(const Book &book) {
    books_.erase(std::find(books_.begin(),books_.end(), book));

}

std::ostream &operator<<(std::ostream &os, const Patron &patron) {
    os << "Name: " << patron.get_name() << "\n"
        << "Card number: " << patron.get_card_number() << "\n";
    return os;
}
