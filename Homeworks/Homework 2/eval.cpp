#include <iostream>
#include <stack>
#include <string>
#include <cassert>
using namespace std;

int precedence(char c);
string deleteSpaces(string infix);
bool checkParen(string infix);
int convert(string infix, string& postfix);

int evaluate(string infix, string& postfix, bool& result);
  // Evaluates a boolean expression
  //   If infix is a syntactically valid infix boolean expression,
  //   then set postfix to the postfix form of that expression, set
  //   result to the value of the expression, and return zero.  If
  //   infix is not a syntactically valid expression, return 1; in
  //   that case, postfix may or may not be changed, but result must
  //   be unchanged.


string deleteSpaces(string infix) {
    string result;
    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] != ' ') result += infix[i];
    }
    return result;
}

bool checkParen(string infix) {
    int closedP = 0;
    int openP = 0;
    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];
        if (ch == '(') openP++;
        if (ch == ')') closedP++;
    }
    
    if (closedP != openP) return false;
    
    stack<char> s;
    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];
        switch(ch) {
            case '(':
                s.push(ch);
                break;
            case ')':
                if (s.empty() || s.top() != '(') return false;
                s.pop();
                break;
        }
    }
    
    return s.empty();
}

int precedence(char c) {
    switch (c) {
        case '!':
            return 3;
        case '&':
            return 2;
        case '^':
            return 1;
        default:
            return 0;
    }
}

int convert(string infix, string& postfix) {

    if (!checkParen(infix)) return 1;
    infix = deleteSpaces(infix);
    
    postfix = "";
    stack<char> s;
    for (int i = 0; i < infix.size(); i++) {
        char ch = infix[i];
        switch (ch) {
            case 'T':
            case 'F':
                if (i > 0)
                    if (infix[i - 1] == 'T' || infix[i - 1] == 'F' || infix[i - 1] == ')') return 1;
                postfix += ch;
                break;
            case '!':
            case '(':
                if (i > 0)
                    if (infix[i - 1] == 'T' || infix[i - 1] == 'F' || infix[i - 1] == ')') return 1;
                s.push(ch);
                break;
            case ')':
                if (i > 0)
                    if (infix[i - 1] == '!' || infix[i - 1] == '&' || infix[i - 1] == '^' || infix[i - 1] == '(') return 1;
                while (s.top() != '(') {
                    postfix += s.top();
                    s.pop();
                }
                s.pop();
                break;
            case '&':
            case '^':
                if (i > 0)
                    if (infix[i - 1] == '!' || infix[i - 1] == '&' || infix[i - 1] == '^' || infix[i - 1] == '(') return 1;
                
                while (!s.empty() && s.top() != '(' && precedence(ch) <= precedence(s.top())) {
                    postfix += s.top();
                    s.pop();
                }
                s.push(ch);
                break;
            case ' ':
                break;
            default:
                return 1;
                break;
                
        }
        
    }
    
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    
    return 0;
}

int evaluate(string infix, string& postfix, bool& result) {
    
    int res = convert(infix, postfix);
    
    if (res == 1) return 1;
    
    stack<char> s;
    for (int i = 0; i < postfix.size(); i++) {
        char ch = postfix[i];
        if (ch == 'T' || ch == 'F') {
            s.push(ch);
        }
        else if (ch == '!') {
            if (s.empty()) return 1;
            char op1 = s.top();
            s.pop();
            if (op1 == 'T') s.push('F');
            if (op1 == 'F') s.push('T');
        }
        else if (ch == '&') {
            if (s.empty()) return 1;
            char op1 = s.top();
            s.pop();
            
            if (s.empty()) return 1;
            char op2 = s.top();
            s.pop();
            
            if (op1 == 'F' || op2 == 'F') s.push('F');
            else s.push('T');
        }
        else {
            if (s.empty()) return 1;
            char op1 = s.top();
            s.pop();
            
            if (s.empty()) return 1;
            char op2 = s.top();
            s.pop();
            
            if ((op1 == 'T' && op2 == 'F') || (op1 == 'F' && op2 == 'T')) s.push('T');
            else s.push('F');
        }
    }
    
    if (s.size() != 1) return 1;
    if (s.top() == 'T') result = true;
    else result = false;
    
    return 0;
}

int main()
{
string pf;
bool answer;
assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
assert(evaluate("T^", pf, answer) == 1);
assert(evaluate("F F", pf, answer) == 1);
assert(evaluate("TF", pf, answer) == 1);
assert(evaluate("()", pf, answer) == 1);
assert(evaluate("()T", pf, answer) == 1);
assert(evaluate("T(F^T)", pf, answer) == 1);
assert(evaluate("T(&T)", pf, answer) == 1);
assert(evaluate("(T&(F^F)", pf, answer) == 1);
assert(evaluate("T|F", pf, answer) == 1);
assert(evaluate("", pf, answer) == 1);
assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0
                       &&  pf == "FF!TF&&^"  &&  !answer);
assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
}
