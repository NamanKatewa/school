#include "Polynomial.h"

Polynomial::Polynomial() : head(nullptr) {}

Polynomial::~Polynomial() {
    TermNode *current = head;
    while (current != nullptr) {
        TermNode *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
}

void Polynomial::insertTerm(int coeff, int exp) {
    if (coeff == 0) return;

    TermNode *newNode = new TermNode(coeff, exp);

    if (head == nullptr || exp > head->exponent) {
        newNode->next = head;
        head = newNode;
        return;
    }

    TermNode *current = head;
    while (current->next != nullptr && exp < current->next->exponent) {
        current = current->next;
    }

    if (current->exponent == exp) {
        current->coefficient += coeff;
        if (current->coefficient == 0) { 
            TermNode* temp = head;
            if (head->exponent == exp) {
                head = head->next;
                delete temp;
                return;
            }
            TermNode* prev = head;
            while(prev->next != nullptr && prev->next->exponent != exp) {
                prev = prev->next;
            }
            temp = prev->next;
            prev->next = temp->next;
            delete temp;
        }
        delete newNode; 
    } else {
        newNode->next = current->next;
        current->next = newNode;
    }
}


Polynomial Polynomial::add(const Polynomial &other) const {
    Polynomial result;
    TermNode *current = head;
    while (current != nullptr) {
        result.insertTerm(current->coefficient, current->exponent);
        current = current->next;
    }

    current = other.head;
    while (current != nullptr) {
        result.insertTerm(current->coefficient, current->exponent);
        current = current->next;
    }
    return result;
}

int Polynomial::compare(const Polynomial &other) const {
    TermNode *p1 = head;
    TermNode *p2 = other.head;

    while (p1 != nullptr && p2 != nullptr) {
        if (p1->exponent > p2->exponent) return 1; 
        if (p1->exponent < p2->exponent) return -1; 

        if (p1->coefficient > p2->coefficient) return 1; 
        if (p1->coefficient < p2->coefficient) return -1; 

        p1 = p1->next;
        p2 = p2->next;
    }

    if (p1 != nullptr) return 1; 
    if (p2 != nullptr) return -1; 

    return 0; 
}

void Polynomial::print() const {
    if (head == nullptr) {
        std::cout << "0" << std::endl;
        return;
    }

    std::cout << "\033[1;36m"
              << std::left << std::setw(15) << "Coefficient"
              << std::setw(15) << "Exponent" << std::endl;
    std::cout << std::string(30, '-') << "\033[0m" << std::endl;

    TermNode *current = head;
    while (current != nullptr) {
        std::cout << "\033[1;32m" // Bold Green
                  << std::left << std::setw(15) << current->coefficient
                  << std::setw(15) << current->exponent << "\033[0m" << std::endl;
        current = current->next;
    }
}