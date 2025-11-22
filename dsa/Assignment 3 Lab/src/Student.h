#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include <iomanip> 

class Student {
private:
    int studentID;
    std::string studentName;
    double grade;
    std::string courseDetails;

public:
    
    Student();

    
    Student(int id, const std::string& name, double g, const std::string& course);

    
    int getStudentID() const;
    std::string getStudentName() const;
    double getGrade() const;
    std::string getCourseDetails() const;

    
    void setStudentID(int id);
    void setStudentName(const std::string& name);
    void setGrade(double g);
    void setCourseDetails(const std::string& course);

    
    void printRow() const;

    
    bool operator<(const Student& other) const {
        return grade < other.grade;
    }
};

#endif 
