#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <iomanip>
#include <windows.h> 

struct TermNode {
    int coefficient;
    int exponent;
    TermNode *next;

    TermNode(int coeff, int exp) : coefficient(coeff), exponent(exp), next(nullptr) {}
};

class Polynomial {
private:
    TermNode *head;

public:
    Polynomial();
    ~Polynomial();

    void insertTerm(int coeff, int exp);
    Polynomial add(const Polynomial &other) const;
    int compare(const Polynomial &other) const;
    void print() const;
};

#endif 