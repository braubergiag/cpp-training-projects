#include "../include/student_info.h"
#include "../include/grader_util.h"


std::istream &read(std::istream &is, student_info &st) {
    is >> st.name >> st.midterm >> st.final;

    read_hw(is,st.homeworks);

    return is;
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

bool compare(const student_info &lhs, const student_info &rhs) {
    return lhs.name < rhs.name;
}

std::vector<student_info> extract_fails(std::vector<student_info> &students) {
    auto it = std::stable_partition(students.begin(), students.end(), pass_grade);
    std::vector<student_info> fail(it, students.end());
    students.erase(it,students.end());

    return fail;
}

std::vector<student_info> extract_didnt_hw(std::vector<student_info> &students) {
    auto it = std::stable_partition(students.begin(), students.end(), did_all_hw);
    std::vector<student_info> didnt(it,students.end());
    students.erase(it,students.end());
    return didnt;
}
