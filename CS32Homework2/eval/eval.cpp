#include "Map.h"
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool checkPrecedence(char x, char y);
bool checkOperand(char x);
bool applyOperation(int op1, int op2, char binaryOperator, int& answer);

int evaluate(string infix, const Map& values, string& postfix, int& result) {
	// Evaluates an integer arithmetic expression
	//   If infix is a syntactically valid infix integer expression whose
	//   only operands are single lower case letters (whether or not they
	//   appear in the values map), then postfix is set to the postfix
	//   form of the expression; if not, postfix may or may not be
	//   changed, result is unchanged, and the function returns 1.  If
	//   infix is syntactically valid but contains at least one lower
	//   case letter operand that does not appear in the values map, then
	//   result is unchanged and the function returns 2.  If infix is
	//   syntactically valid and all its lower case operand letters
	//   appear in the values map, then if evaluating the expression
	//   (using for each letter in the expression the value in the map
	//   that corresponds to it) attempts to divide by zero, then result
	//   is unchanged and the function returns 3; otherwise, result is
	//   set to the value of the expression and the function returns 0.
    postfix = "";
    stack<char> operatorStack;
    bool needOp = false;
    for (int i = 0; i < infix.size();i++) {
        if (infix[i] >= 'a' && infix[i] <= 'z') {
            postfix += infix[i];
            needOp = false;
            continue;
        }
        switch (infix[i]) {
            
            case '(': 
                operatorStack.push(infix[i]);
                needOp = true;
                break;
            case ')': 
                if (needOp) {
                    return 1;
                }
                while (!operatorStack.empty() && operatorStack.top() != '(') {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                if (operatorStack.empty()) {
                    return 1;
                }
                else {
                    operatorStack.pop();
                }
                break;
            case '*':
            case '/':
            case '+':
            case '-':
                if (needOp) {
                    return 1;
                }
                while (!operatorStack.empty() && operatorStack.top() != '(' && !checkPrecedence(infix[i], operatorStack.top())) {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(infix[i]);
                break;
            default:
                if (infix[i] != ' ') {
                    return 1;
                }
                break;
            }
    }
    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    stack<int> operandStack;
    int value;
    for (int i = 0; i < postfix.size(); i++) {
        if (checkOperand(postfix[i])) {
            if (!values.get(postfix[i], value)) {
                return 2;
            }
            operandStack.push(value);
        }
        else if (postfix[i] == '(') {
            return 1;
        }
        else {
            if (operandStack.empty()) {
                return 1;
            }
            int operand2 = operandStack.top();
            operandStack.pop();
            if (operandStack.empty()) {
                return 1;
            }
            int operand1 = operandStack.top();
            operandStack.pop();
            int answer = 0;
            if (!applyOperation(operand1, operand2, postfix[i], answer)) {
                return 3;
            }
            operandStack.push(answer);
        }
    }
    int temp;
    if (!operandStack.empty()) {
        temp = operandStack.top();
        operandStack.pop();
        if (!operandStack.empty()) {
            return 1;
        }
        else {
            result = temp;
        }

    }
    else {
        return 1;
    }
    return 0;
}

bool checkPrecedence(char x, char y) {
    if ((x == '*' || x == '/') && (y == '*' || y == '/' || y == '+' || y == '-')) {
        return true;
    }
    if ((x == '+' || x == '-') && (y == '+' || y != '-')) { 
        return true;
    }
    return false;
}

bool checkOperand(char x) {
    if (x >= 'a' && x <= 'z') {
        return true;
    }
    return false;
}

bool applyOperation(int op1, int op2, char binaryOperator, int& answer) {
    if (binaryOperator == '*') {
        answer = op1 * op2;
    }
    else if (binaryOperator == '/') {
        if (op2 == 0) {
            return false;
        }
        answer = op1 / op2;
    }
    else if (binaryOperator == '+') {
        answer = op1 + op2;
    }
    else if (binaryOperator == '-') {
        answer = op1 - op2;
    }
    return true;
}

int main()
{
    char vars[] = { 'a', 'e', 'i', 'o', 'u', 'y', '#' };
    int  vals[] = { 3,  -9,   6,   2,   4,   1 };
    Map m;
    for (int k = 0; vars[k] != '#'; k++)
        m.insert(vars[k], vals[k]);
    string pf;
    int answer;

    /* int temp = evaluate("a+ e", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    answer = 999;
    temp = evaluate("", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    temp = evaluate("a+", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    temp = evaluate("a i", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    temp = evaluate("ai", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    temp = evaluate("()", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    temp = evaluate("()o", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    temp = evaluate("y(o+u)", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    evaluate("y(*o)", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    evaluate("a+E", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    temp = evaluate("(a+(i-o)", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    // unary operators not allowed:
    temp = evaluate("-a", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    temp = evaluate("a*b", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    temp = evaluate("y +o *(   a-u)  ", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    answer = 999;
    temp = evaluate("o/(y-y)", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    temp = evaluate(" a  ", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;
    temp = evaluate("((a))", m, pf, answer);
    cout << temp << " " << pf << " " << answer << endl;*/

    assert(evaluate("a+ e", m, pf, answer) == 0 && pf == "ae+" && answer == -6);
    answer = 999;
    assert(evaluate("", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a+", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a i", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("ai", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("()", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("()o", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("y(o+u)", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("y(*o)", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a+E", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("(a+(i-o)", m, pf, answer) == 1 && answer == 999);
    // unary operators not allowed:
    assert(evaluate("-a", m, pf, answer) == 1 && answer == 999);
    assert(evaluate("a* b", m, pf, answer) == 2 &&
        pf == "ab*" && answer == 999);
    assert(evaluate("y +o *(   a-u)  ", m, pf, answer) == 0 &&
        pf == "yoau-*+" && answer == -1);
    answer = 999;
    assert(evaluate("o/(y-y)", m, pf, answer) == 3 &&
        pf == "oyy-/" && answer == 999);
    assert(evaluate(" a  ", m, pf, answer) == 0 &&
        pf == "a" && answer == 3);
    assert(evaluate("((a))", m, pf, answer) == 0 &&
        pf == "a" && answer == 3);
    cout << "Passed all tests" << endl;
    return 0;
}