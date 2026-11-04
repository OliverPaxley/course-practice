// Debugging Practice 5 - Ternary and Comma Operators
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

int main() {
    int x = -10;
    int sign = (x < 0 ? -1 : 1);
    cout << sign;

    int a = 1, b = 2, c = 3;
    int result = (a = 5, b = 10, a + b);
    cout << result;

    return 0;
}

/*
Expected Output: -115
Explanation: x=-10, so x<0 is true, sign=-1. Comma: a=5, b=10, result=a+b=15.
*/