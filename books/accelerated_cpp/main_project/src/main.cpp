#include <iostream>
#include <vector>
#include <iomanip>
#include "../include/student_info.h"
#include "../include/grader_util.h"




int main()
{

    std::vector<student_info> students;
    student_info st;

    size_t max_len = 0;
    while(read(std::cin,st)) {
        max_len = std::max(max_len, st.name.size());
        students.push_back(st);

    }
    std::vector<student_info> students_failed_hw = extract_didnt_hw(students);
    write_analysis(std::cout, "median", median_analysis, students, students_failed_hw);
    write_analysis(std::cout, "average", average_analysis, students, students_failed_hw);
    write_analysis(std::cout, "optimistic median", optimistic_median_analysis, students, students_failed_hw);

#if 0
    std::sort(students_info.begin(), students_info.end(), compare);

    for (auto && stud: students_info) {

        try {
            double final_grade = grade(stud);
            std::cout <<  stud.name << " " << std::string(max_len + 1 - stud.name.size(),' ') << final_grade << "\n";

        } catch (std::exception & ex) {
            std::cout << ex.what() << "\n";
        }
    }

#endif

}