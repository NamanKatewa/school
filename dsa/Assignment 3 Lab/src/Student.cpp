#include "Student.h"


Student::Student() : studentID(0), studentName(""), grade(0.0), courseDetails("") {}


Student::Student(int id, const std::string& name, double g, const std::string& course)
    : studentID(id), studentName(name), grade(g), courseDetails(course) {}


int Student::getStudentID() const {
    return studentID;
}

std::string Student::getStudentName() const {
    return studentName;
}

double Student::getGrade() const {
    return grade;
}

std::string Student::getCourseDetails() const {
    return courseDetails;
}


void Student::setStudentID(int id) {
    studentID = id;
}

void Student::setStudentName(const std::string& name) {
    studentName = name;
}

void Student::setGrade(double g) {
    grade = g;
}

void Student::setCourseDetails(const std::string& course) {
    courseDetails = course;
}


void Student::printRow() const {
    
    
    std::cout << std::left << std::setw(8) << studentID
              << std::left << std::setw(25) << studentName
              << std::left << std::setw(8) << std::fixed << std::setprecision(2) << grade
              << std::left << std::setw(20) << courseDetails << std::endl;
}
