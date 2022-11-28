//
// Created by igor on 28.11.22.
//

#include "../include/library.h"
#include "../include/rapidcsv.h"
void library::read_from_file() {



    rapidcsv::Document doc("../data/greads.csv");

    std::vector<std::string> titles = doc.GetColumn<std::string>("title");
    std::vector<std::string> authors = doc.GetColumn<std::string>("authors");
    std::vector<std::string> isbns = doc.GetColumn<std::string>("isbn");
    std::cout << "Read " << titles.size() << " values." << std::endl;

    const int copy_amount = 1, copy_available = 1;
    for (int i = 0; i < titles.size(); ++i) {
        BookInfo bookInfo{Book(authors[i],titles[i],isbns[i]),copy_amount,copy_available};
        books_.emplace_back(bookInfo);
    }

}
