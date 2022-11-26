//
// Created by igor on 26.11.22.
//

#ifndef STUDENT_EXAM_DATE_H
#define STUDENT_EXAM_DATE_H

#include <iostream>

class Date {

public:
    Date(int year, int month, int day) : year_(year), month_(month), day_(day) {


    }


    friend std::ostream & operator<<(std::ostream & out,const Date & date);


private:
    int year_;
    int month_;
    int day_;

};






#endif //STUDENT_EXAM_DATE_H
