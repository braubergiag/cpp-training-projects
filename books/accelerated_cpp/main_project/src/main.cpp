#include <iostream>
#include <vector>
#include "../include/student_info.h"
#include "../include/grader_util.h"




int main(){



    std::vector<student_info> students_info;
    int numberOfStudents = 0;
    std::cout << "Enter number of students: ";
    std::cin >> numberOfStudents;
    for (int i = 0; i < numberOfStudents; ++i){

        std::string name;
        std::cin >> name;
        double midterm, final;
        std::cin >> midterm >> final;


        std::vector<double> homework_grades;
        read_hw(std::cin,homework_grades);

        students_info.push_back({name,final,midterm,homework_grades});

    }

    for (auto && stud: students_info) {
        std::cout << stud.name << " " << final_grade(stud) << "\n";
    }



}