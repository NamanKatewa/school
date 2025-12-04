#include<vector>
#include<string>
#include<stdexcept>
#include<iostream>
using namespace std;

class CharStack {
    vector<char> data;
public:
    void push(char c) {
        data.push_back(c);
    }
    void pop() {
        if (!data.empty()) data.pop_back();
    }
    char top() const {
        if (data.empty()) {
            throw runtime_error("Stack underflow");
        }
        return data.back();
    }
    bool empty() const {
        return data.empty();
    }
};

int precedence(char op) {
    switch (op) {
        case '^': return 3;
        case '*':
        case '/': return 2;
        case '+':
        case '-': return 1;
        default:  return 0;
    }
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

string infixToPostfix(const string &infix) {
    CharStack st;
    string postfix;

    for (char c : infix) {
        if (c == ' ') {
            continue;
        }
        if (isalnum(static_cast<unsigned char>(c))) {
            postfix += c;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                postfix += st.top();
                st.pop();
            }
            if (!st.empty() && st.top() == '(') {
                st.pop();
            }
        } else if (isOperator(c)) {
            while (!st.empty() && isOperator(st.top())) {
                char topOp = st.top();
                int pTop = precedence(topOp);
                int pCur = precedence(c);

                bool shouldPop =
                    (pTop > pCur) ||
                    (pTop == pCur && c != '^');

                if (shouldPop) {
                    postfix += topOp;
                    st.pop();
                } else {
                    break;
                }
            }
            st.push(c);
        }
    }

    while (!st.empty()) {
        if (st.top() != '(' && st.top() != ')')
            postfix += st.top();
        st.pop();
    }

    return postfix;
}

int main(){
    string infix;
    cout << "Enter infix expression: ";
    getline(cin, infix);

    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;
    return 0;
}