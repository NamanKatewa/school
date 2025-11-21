#ifndef STUDENT_H
#define STUDENT_H

#include <string>

struct Student {
    int rollNumber;
    std::string name;
    float marks;
    std::string course;

    Student() : rollNumber(0), name(""), marks(0.0f), course("") {}

    Student(int rn, std::string n, float m, std::string c)
        : rollNumber(rn), name(std::move(n)), marks(m), course(std::move(c)) {}
};

#endif