#include <iostream>

#include "../include/book.h"
#include "../include/library.h"
#include "../include/query.h"


using std::cout;
using std::cin;
using std::string;
int main(){

    library lib;
    lib.read_from_file();


    std::string command;
    while (std::cin >> command) {
        auto query = get_query_type(command);
        std::string name, book_title;
        switch (query) {
            case lib_query::AddPatron:
                std::cin >> name;
                lib.add_patron(name);
                break;
            case lib_query::BorrowBook:
                std::cin >> name >> book_title;
                lib.issue_book(name, book_title);
                break;

            case lib_query::ReturnBook:
                std::cin >> name >> book_title;
                lib.take_book(name, book_title);
                break;
            case lib_query::PrintPatronInfo:
            {
                std::cin >> name;
                std::optional<Patron> patron = lib.patron(name);
                if (patron != std::nullopt) {
                    cout << patron.value();
                }
                break;
            }
            case lib_query::PrintBookInfo:
            {
                std::cin.get();
                std::getline(std::cin,book_title);
                std::optional<Book> book = lib.book(book_title);
                if (book != std::nullopt){
                    cout << book.value();
                }
                break;
            }

            default:
                std::cout << "Wrong command: " << command << "\n";
                break;
        }




    }


}