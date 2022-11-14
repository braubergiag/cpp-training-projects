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


std::istream & read( std::istream & is,student_info & stud_info);
std::istream  & read_hw(std::istream & is, std::vector<double> & grades);
bool compare(const student_info & lhs, const student_info& rhs);
std::vector<student_info> extract_fails(std::vector<student_info> & students);
std::vector<student_info> extract_didnt_hw(std::vector<student_info> & students);


#endif //STUDENT_EXAM_STUDENT_INFO_H
