#include <numeric>
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
double grade(const student_info &st) {
    return grade(st.midterm, st.final, st.homeworks);
}

double grade(double midterm, double final, const std::vector<double> &homework) {
    if (homework.empty()) {
        throw std::domain_error("Student doesn't have grades for homeworks.");
    }
    return grade(midterm,final, median(homework));
}

double grade(double midterm, double final, double homework) {
    return  0.2 * midterm + 0.4 * final + 0.4 * homework;
}

bool did_all_hw(const student_info &st) {
    return std::find(st.homeworks.begin(),st.homeworks.end(),0) == st.homeworks.end();
}

double grade_aux(const student_info &st) {
    try {
        return grade(st);
    } catch (std::domain_error & ){
        return grade(st.midterm,st.final,0);
    }
}

double median_analysis(const std::vector<student_info> &students) {
    std::vector<double> grades;
    std::transform(students.begin(), students.end(), std::back_inserter(grades), grade_aux);
    return median(grades);
}

void write_analysis(std::ostream &os, const std::string &name, AnalysisFunc analysisFunc, const std::vector<student_info> &did,
                    const std::vector<student_info> &didnt) {


    os << name << " : median(did) = " << analysisFunc(did)
                << ", median(didnt) = " << analysisFunc(didnt) << std::endl;
}

double average(const std::vector<double> &v) {
    return std::accumulate(v.begin(),v.end(),0.0) / v.size();
}

double average_grade(const student_info &st) {
    return grade(st.midterm,st.final, average(st.homeworks));
}

double average_analysis(const std::vector<student_info> &students) {
    std::vector<double> grades;
    std::transform(students.begin(),students.end(),
                   std::back_inserter(grades), average_grade);
    return median(grades);
}

double optimistic_median_analysis(const std::vector<student_info> &students) {
    std::vector<double> grades;
    std::transform(students.begin(),students.end(),
                   std::back_inserter(grades), optimistic_median);
    return median(grades);

}

double optimistic_median(const student_info &st) {
    std::vector<double> nonzero;
    std::remove_copy(st.homeworks.begin(), st.homeworks.end(),
                     std::back_inserter(nonzero),0);
    if (nonzero.empty()) {
        return grade(st.midterm, st.final, 0);
    } else {
        return grade(st.midterm, st.final,median(nonzero));
    }
}

bool pass_grade(student_info &st) {
    return !fail_grade(st);
}

bool fail_grade(student_info &st) {
    return grade(st) < 60;
}

