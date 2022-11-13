#include "../include/grader_util.h"

double median( std::vector<double>  grades){



    if (grades.empty()) {
        throw std::domain_error("Median of an empty vector.");
    }

    size_t mid = grades.size() / 2;
    std::sort(grades.begin(), grades.end());
    double median = grades.size() % 2 == 0 ?
                    ( grades[mid - 1] + grades[mid] ) / 2 :
                    grades[mid];

    return  median;

}



double final_grade(const student_info &stud_info) {
    if (stud_info.homeworks.empty()) {
        throw std::domain_error("Student doesn't have grades for homeworks.");
    }
    return 0.4 * median(stud_info.homeworks) + 0.4 * stud_info.final + 0.2 * stud_info.midterm;

}

std::istream &read_hw(std::istream &is, std::vector<double> &grades) {

    if (is) {
        grades.clear();
        double grade = 0;
        while (is >> grade) {
            grades.push_back(grade);
        }

        is.clear();
    }


    return is;
}
