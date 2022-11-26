#include "../include/date.h"



std::ostream &operator<<(std::ostream &os,const Date &date) {
    os << date.year_ << "-" << date.month_ << "-" << date.day_;
    return os;;
}
