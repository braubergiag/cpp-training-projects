#include <gtest/gtest.h>
#include <sstream>
#include "../include/library.h"


using std::string;

TEST(LibraryCore,BookInfo){
    library lib;
    lib.read_from_file();
    {
        std::istringstream iss("PRINT_BOOK_INFO Vineland");
        std::string command, book_title;
        iss >> command >> book_title;
        std::optional<Book> book = lib.book(book_title);
        ASSERT_EQ(book->get_author(),"Thomas Pynchon");
        ASSERT_EQ(book->get_title(),"Vineland");
    }
    {

        std::istringstream iss("PRINT_BOOK_INFO Running Dog");
        std::string command, book_title;
        iss >> command ;
        iss.get();
        getline(iss,book_title);
        std::optional<Book> book = lib.book(book_title);
        ASSERT_EQ(book->get_author(),"Don DeLillo");
        ASSERT_EQ(book->get_title(),"Running Dog");
    }

}

TEST(LibraryCore,AddPatron){
    library lib;
    lib.read_from_file();
    std::istringstream iss("ADD_PATRON Igor");
    string command, name;
    iss >> command >> name;
    lib.add_patron(name);
    std::optional<Patron> patron = lib.patron(name);
    ASSERT_EQ(patron->get_name(), "Igor");
    ASSERT_EQ(patron->get_card_number(),1);

}