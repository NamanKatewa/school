#include "PostfixEvaluator.hpp"
#include "StackArray.hpp"
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <cctype>

int PostfixEvaluator::evaluate(const std::string &expr) {
    std::istringstream iss(expr);
    std::string token;
    StackArray stack(expr.length());

    while (iss >> token) {
        if (isdigit(token[0]) || (token.length() > 1 && token[0] == '-')) {
            try {
                stack.push(std::stoi(token));
            } catch (const std::invalid_argument& e) {
                throw std::invalid_argument("Invalid number format in expression.");
            }
        } else if (token.length() == 1 && std::string("+-*/^").find(token) != std::string::npos) {
            if (stack.isEmpty()) throw std::runtime_error("Not enough operands for operator " + token);
            int b = stack.pop();
            if (stack.isEmpty()) throw std::runtime_error("Not enough operands for operator " + token);
            int a = stack.pop();

            switch (token[0]) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/':
                    if (b == 0) throw std::runtime_error("Division by zero.");
                    stack.push(a / b);
                    break;
                case '^': stack.push(static_cast<int>(pow(a, b))); break;
            }
        } else {
            if (!token.empty())
                throw std::invalid_argument("Invalid token in expression: " + token);
        }
    }

    if (stack.isEmpty()) {
        if (expr.empty()) return 0; // Or throw error, depending on desired behavior for empty expression
        throw std::runtime_error("Expression is empty or invalid.");
    }
    
    int result = stack.pop();

    if (!stack.isEmpty()) {
        throw std::runtime_error("Extra operands remaining.");
    }

    return result;
}
