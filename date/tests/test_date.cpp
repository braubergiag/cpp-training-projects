//
// Created by igor on 26.11.22.
//
#include <gtest/gtest.h>
#include "../include/date.h"
#include <sstream>


TEST(Date,DateCtr){

    Date d{2020,12,23};
    std::stringstream s;
    s << d;
    ASSERT_EQ(s.str(),"2020-12-23");

}

