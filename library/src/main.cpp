#include <iostream>

#include "../include/book.h"
#include "../include/library.h"


int main(){

    library lib;
    lib.read_from_file();


    std::string command;
    while (std::cin >> command) {
        if (command == "ADD_PATRON"){
            std::string name;
            std::cin >> name;
            lib.add_patron(name);
        }
        else if (command == "BORROW_BOOK") {
            std::string name, book_title;
            std::cin >> name >> book_title;
            lib.issue_book(name, book_title);

        }
        else if (command == "RETURN_BOOK") {
            std::string name, book_title;
            std::cin >> name >> book_title;
            lib.take_book(name, book_title);
        }
        else if (command == "PATRON_INFO") {
            std::string name;
            std::cin >> name;
            lib.patron(name);
        }
        else if (command == "PRINT_BOOK_INFO") {
            std::string book_title;
            std::cin.get();
            std::getline(std::cin >> std::skipws,book_title);
            lib.book(book_title);
        }
        else if (command == "PRINT_PATRONS"){
            lib.print_patrons();
        }

    }


}