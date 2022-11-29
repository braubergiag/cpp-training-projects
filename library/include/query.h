//
// Created by igor on 29.11.22.
//

#ifndef LIBRARY_QUERY_H
#define LIBRARY_QUERY_H

#include <string>

enum class lib_query {
    AddPatron,
    BorrowBook,
    ReturnBook,
    PrintPatronInfo,
    PrintBookInfo,
};


lib_query get_query_type(const std::string & query);
void parse_request(const std::string & request);



#endif //LIBRARY_QUERY_H
