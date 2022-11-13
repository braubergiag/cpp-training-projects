//
// Created by igor on 13.11.22.
//

#ifndef STUDENT_EXAM_GRADER_UTIL_H
#define STUDENT_EXAM_GRADER_UTIL_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "student_info.h"

double median( std::vector<double>  grades);
double final_grade(const student_info &stud_info);
std::istream  & read_hw(std::istream & is, std::vector<double> & grades);


#endif //STUDENT_EXAM_GRADER_UTIL_H
