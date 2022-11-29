//
// Created by igor on 28.11.22.
//

#ifndef LIBRARY_LIBRARY_H
#define LIBRARY_LIBRARY_H

#include "book.h"
#include "patron.h"
#include <vector>
#include <optional>
struct BookInfo {
    Book book;
    int copy_amount;
    int copy_available;
    int book_id;

};
struct Transaction {

    Patron patron;
    Book book;

};
class library {

public:
    void add_patron(const std::string& name);
    void print_patrons() const;
    std::optional<Patron> patron(const std::string& name) const;
    void print_books() const;
    std::optional<Book> book(const std::string& book_title) const;
    void issue_book(const std::string& name, const std::string & book_title);
    void take_book(const std::string& name, const std::string & book_title);
    std::vector<Patron> find_book_copies(std::string book_title);
    void read_from_file();


private:
    auto find_book(const std::string & book_title);
    auto find_book(const std::string & book_title) const;


private:
    inline static int patron_card_number_{0};
    inline static int book_id{0};
    std::vector<BookInfo> books_;
    std::vector<Patron> patrons_;
    std::vector<Transaction> transactions_;
};


#endif //LIBRARY_LIBRARY_H
