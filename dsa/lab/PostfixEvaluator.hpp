#ifndef POSTFIX_EVALUATOR_HPP
#define POSTFIX_EVALUATOR_HPP

#include <string>

class PostfixEvaluator {
public:
    static int evaluate(const std::string &expr);
};

#endif
