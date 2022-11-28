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
               std::string isbn, int copyAmount);

    const std::string &getTitle() const;
    const std::string &getAuthor() const;
    const std::string &getIsbn() const;
    int getCopyAmount() const;
    int getCopyAvailable() const;
public:
    void setAuthor(const std::string &author);
    void setTitle(const std::string &title);
    void setIsbn(const std::string &isbn);
    void setCopyAmount(int copyAmount);
    void setCopyAvailable(int copyAvailable);

private:
    std::string title_;
    std::string author_;
    std::string isbn_;
    int copy_amount_;
    int copy_available_;

};

bool operator==(const Book & lhs, const Book & rhs);
std::ostream & operator<<(std::ostream & os, const Book & book);
#endif //DATE_LIBRARY_H
