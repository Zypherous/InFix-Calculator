/******************************************************/
/* Programmer:Jonathan Rosario                        */
/* Date: 11/01/2020                                   */
/* Purpose:Project 2, in-fix calculator usings stacks */
/******************************************************/
#include <iostream>
#include "StackL.cpp"

using namespace std;

bool isDigit(char);
bool isOperator(char);
int operate(int, int, char);
int precedenceOfOp(char);
int processExpression(string);
//void printInstructions();

int main() {
    cout << processExpression("200 *(_(1)*_(_5))");
    return 0;
}

//Check to see if char is valid number
bool isDigit(char c) {
    return (c >= '0' && c <= '9');
}

//Check to see if char is valid operator
bool isOperator(char c) {
    return (c == '+' ||
        c == '-' ||
        c == '/' ||
        c == '*' ||
        c == '(' ||
        c == ')' ||
        c == '_');
}

//Operate on the expression and return an integer
int operate(int num1, int num2, char op) {
    if (op == '+') {
        return (num1 + num2);
    }
    if (op == '-') {
        return (num1 - num2);
    }
    if (op == '*') {
        return (num1 * num2);
    }
    return (num1 / num2);
}

//Determine precedence of operator
int precedenceOfOp(char op) {
    switch (op) {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    case '_': return 3;
    case '(':
    case ')': return 4;
    default: return -1;
    }
}

// Process the string expression
int processExpression(string exp) {
    Stack<int> values;
    Stack<char> operators;

    int value = 0;
    int position = 0;
    while (position < exp.length()) {
        char cur = exp[position];
        if (isdigit(cur)) {
            /*if (operators.peek() == '_') {
                 value = -1*(value * 10) + static_cast<int>(cur - '0');
                 operators.pop();
             }*/
             //else {
            value = (value * 10) + static_cast<int>(cur - '0');
            //}
        }
        else if (isOperator(cur)) {
            if (cur == '_') {
                operators.push('_');
            }
            else if (cur == '(') {
                operators.push(cur);
                value = 0;
            }
            else if (values.isEmpty()) {
                values.push(value);
                operators.push(cur);
                value = 0;
            }
            else if (cur == ')') {
                values.push(value);
                while (operators.peek() != '(') {
                    cur = operators.peek();
                    operators.pop();
                    value = values.peek();
                    if (cur == '_') {
                        value *= -1;
                        cur = operators.peek();
                    }
                    else {
                        values.pop();
                        int prior = values.peek();
                        values.pop();
                        value = operate(prior, value, cur);
                    }
                }
                operators.pop();
                values.pop();
            }else {
                char priorOp = operators.peek();
                /*if (cur == '_') {
                    value = values.peek();
                    values.pop();
                    value *= -1;
                    cur = operators.peek();
                    operators.pop();
                    values.push(value);
                    value = 0;
                }*/
      /* else*/ if (precedenceOfOp(cur) > precedenceOfOp(priorOp)) {
                        values.push(value);
                        operators.push(cur);
                        value = 0;
                    }
                else {
                    int prior = values.peek();
                    values.pop();
                    int priorOp = operators.peek();
                    operators.pop();
                    prior = operate(prior, value, priorOp);
                    values.push(prior);
                    operators.push(cur);
                    value = 0;
                }
            }
        }
        position++;
    }

    while (!operators.isEmpty()) {
        //char cur = operators.peek();
       /* if (cur == '_') {
            value *= -1;
            operators.pop();
            values.push(value);
            value = 0;
        }*/
      //  else {
            int prior = values.peek();
            values.pop();
            char cur = operators.peek();
            operators.pop();
           while(cur == '_') {
                prior *= -1;
                cur = operators.peek();
                operators.pop();
            }
            value = operate(prior, value, cur);
    }
    return value;
}

// Function to display menu and instructions to user and prompt for input
/*
void printInstructions(){
    cout << "Please enter in an in-fix expression to be evaluated."
        << "\nValid expression includes 0-9, +,-,*, and /."
        << "\nWhat would you like to evaluate?";
    string expression;
    cin >> expression;

}*/
