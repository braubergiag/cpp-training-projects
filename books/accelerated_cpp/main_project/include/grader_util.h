//
// Created by igor on 13.11.22.
//

#ifndef STUDENT_EXAM_GRADER_UTIL_H
#define STUDENT_EXAM_GRADER_UTIL_H

#include <vector>
#include <iostream>
#include <algorithm>
#include "student_info.h"


typedef double  (*AnalysisFunc)(const std::vector<student_info> &);

double average(const std::vector<double> & v);
double average_grade(const student_info & st);
double median( std::vector<double>  grades);

double optimistic_median(const student_info & st);
double median_analysis(const std::vector<student_info> & students);
double average_analysis(const std::vector<student_info> & students);
double optimistic_median_analysis(const std::vector<student_info> & students);


bool pass_grade(student_info & st);
bool fail_grade(student_info & st);

double grade(const student_info &st);
double grade(double midterm, double final, double homework);
double grade(double midterm, double final, const std::vector<double>& homework);
double grade_aux(const student_info & st);
bool did_all_hw(const student_info & st);

void write_analysis(std::ostream & os,const std::string & name,
                    AnalysisFunc func,const std::vector<student_info>& did,
                    const std::vector<student_info>& didnt);
#endif //STUDENT_EXAM_GRADER_UTIL_H
