//
// Created by igor on 28.11.22.
//

#include <optional>
#include "../include/library.h"
#include "../include/rapidcsv.h"
void library::read_from_file() {



    rapidcsv::Document doc("../data/greads.csv");
    std::vector<std::string> titles, authors, isbns;
    titles = doc.GetColumn<std::string>("title");
    authors = doc.GetColumn<std::string>("authors");
    isbns = doc.GetColumn<std::string>("isbn");

    const int copy_amount = 3, copy_available = 3;
    for (int i = 0; i < titles.size(); ++i) {
        BookInfo bookInfo{Book(authors[i],titles[i],isbns[i]),
                          ++book_id,
                          copy_amount,
                          copy_available};
        books_.emplace_back(bookInfo);
    }

}

void library::add_patron(const std::string& name) {
    patrons_.emplace_back(name,++patron_card_number_);

}

void library::print_patrons() const {
    for (const auto & patron: patrons_) {
        std::cout << patron.get_name() << " " << patron.get_card_number() << "\n";
    }

}

std::optional<Patron> library::patron(const std::string &name) const {
    auto patron_it = std::find_if(patrons_.begin(),
                                  patrons_.end(),
                                  [&name](const Patron & patron) {
        return patron.get_name() == name;
    });
    if (patron_it != patrons_.end()) {
        return *patron_it;
    }
    return std::nullopt;
}

auto  library::find_book(const std::string &book_title)  {

    return std::find_if(books_.begin(), books_.end(),[&book_title](const BookInfo & bookInfo) {
        return bookInfo.book.get_title() == book_title;
    });
}

auto library::find_book(const std::string &book_title) const {
    return std::find_if(books_.begin(), books_.end(),[&book_title](const BookInfo & bookInfo) {
        return bookInfo.book.get_title() == book_title;
    });
}

void library::issue_book(const std::string &name, const std::string &book_title) {
    auto patron_it = std::find_if(patrons_.begin(), patrons_.end(),[&name](const Patron  & patron){
       return patron.get_name() == name;
    });
    auto book_it = find_book(book_title);

    if (patron_it == patrons_.end()) {
        std::cout << "Patron with name " << name << " not found\n";
        return;
    }
    if (book_it == books_.end()) {
        std::cout << "Book with title " << book_title << " not found\n";
        return;
    }
    if (book_it->copy_amount == 0 || book_it->copy_available == 0){
        std::cout << "There are not free copies for now.\n";
        return;
    }

    patron_it->borrow_book(book_it->book);
    book_it->copy_available--;


}

std::optional<Book> library::book(const std::string &book_title) const {
    auto book_it = find_book(book_title);
    if (book_it != books_.end()){
        return book_it->book;
    }

    return std::nullopt;
}

void library::take_book(const std::string &name, const std::string &book_title) {
    auto patron_it = std::find_if(patrons_.begin(), patrons_.end(),[&name](const Patron  & patron){
        return patron.get_name() == name;
    });
    auto book_it = find_book(book_title);

    if (patron_it == patrons_.end()) {
        std::cout << "Patron with name " << name << " not found\n";
        return;
    }
    if (book_it == books_.end()) {
        std::cout << "Book with title " << book_title << " not found\n";
        return;
    }
    auto patrons_books = patron_it->get_books();
    if (std::find(patrons_books.begin(),
                  patrons_books.end(), book_it->book) == patrons_books.end()){
        std::cout << "Patron doesn't have book with title " << book_title << "\n";
        return;
    }
    patron_it->return_book(book_it->book);
    book_it->copy_available++;




}
