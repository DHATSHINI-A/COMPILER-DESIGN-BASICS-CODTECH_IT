#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string expr;
int pos = 0;

// Skip whitespaces
void skipSpaces() {
    while (pos < expr.length() && expr[pos] == ' ')
        pos++;
}

// Forward declarations
int expression();
int term();
int factor();

// expression → term {( + | - ) term}
int expression() {
    int value = term();
    skipSpaces();

    while (pos < expr.length()) {
        if (expr[pos] == '+') {
            pos++;
            value += term();
        } else if (expr[pos] == '-') {
            pos++;
            value -= term();
        } else {
            break;
        }
        skipSpaces();
    }
    return value;
}

// term → factor {( * | / ) factor}
int term() {
    int value = factor();
    skipSpaces();

    while (pos < expr.length()) {
        if (expr[pos] == '*') {
            pos++;
            value *= factor();
        } else if (expr[pos] == '/') {
            pos++;
            value /= factor();
        } else {
            break;
        }
        skipSpaces();
    }
    return value;
}

// factor → number | ( expression )
int factor() {
    skipSpaces();

    if (expr[pos] == '(') {
        pos++;
        int value = expression();
        pos++; // skip ')'
        return value;
    }

    int num = 0;
    while (pos < expr.length() && isdigit(expr[pos])) {
        num = num * 10 + (expr[pos] - '0');
        pos++;
    }
    return num;
}

int main() {
    cout << "Enter arithmetic expression: ";
    getline(cin, expr);

    int result = expression();
    cout << "Result: " << result << endl;

    return 0;
}
