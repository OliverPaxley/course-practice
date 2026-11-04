// Debugging Practice 15 - Operator Precedence
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

int main() {
    int a = 2 + 3 * 4;
    cout << a;

    int b = (2 + 3) * 4;
    cout << b;

    int c = 10 / 3;
    cout << c;

    int d = 10 % 3;
    cout << d;

    return 0;
}

/*
Expected Output: 142031
Explanation: 2+3*4 = 2+12 = 14 (precedence)
(2+3)*4 = 5*4 = 20 (parentheses)
10/3 = 3 (integer division)
10%3 = 1 (modulo)
*/