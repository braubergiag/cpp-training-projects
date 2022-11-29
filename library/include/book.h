//
// Created by igor on 28.11.22.
//

#ifndef DATE_LIBRARY_H
#define DATE_LIBRARY_H

#include <string>
#include <ostream>

enum class Genre {

};


class Book {

public:

    Book() {};
    Book(std::string author,
               std::string title,
               std::string isbn);

    const std::string &get_title() const;
    const std::string &get_author() const;
    const std::string &get_isbn() const;
public:
    void set_author(const std::string &author);
    void set_title(const std::string &title);
    void set_isbn(const std::string &isbn);

private:
    std::string title_;
    std::string author_;
    std::string isbn_;
};

bool operator==(const Book & lhs, const Book & rhs);
std::ostream & operator<<(std::ostream & os, const Book & book);
#endif //DATE_LIBRARY_H
