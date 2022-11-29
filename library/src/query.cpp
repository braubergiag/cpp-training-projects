#include "../include/query.h"
#include <sstream>
lib_query get_query_type(const std::string &query) {
    if (query == "ADD_PATRON"){
        return lib_query::AddPatron;
    }
    else if (query == "BORROW_BOOK"){
        return lib_query::BorrowBook;
    }
    else if (query == "RETURN_BOOK"){
        return  lib_query::ReturnBook;
    }
    else if (query == "PRINT_BOOK_INFO"){
        return lib_query::PrintBookInfo;
    }
    else if (query == "PRINT_PATRON_INFO"){
        return lib_query::PrintPatronInfo;
    }
}

void parse_request(const std::string &request)
{
    std::istringstream iss(request);
    std::string command;
    iss >> command;
    auto query = get_query_type(command);

    switch (query) {


    }


}
