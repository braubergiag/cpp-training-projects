//
// Created by igor on 13.11.22.
//

#ifndef STUDENT_EXAM_STUDENT_INFO_H
#define STUDENT_EXAM_STUDENT_INFO_H

#include <vector>
#include <istream>
#include <string>
struct student_info {
    std::string name;
    double final;
    double midterm;
    std::vector<double> homeworks;




};


std::istream & operator<<( std::istream & is,student_info & stud_info);


#endif //STUDENT_EXAM_STUDENT_INFO_H
