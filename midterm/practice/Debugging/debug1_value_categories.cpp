// Debugging Practice 1 - Value Categories and Expressions
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

int main() {
    // Question 1: Value categories
    int x = 10;
    int y = x + 5;
    int&& z = x + 5;
    cout << x << y << z;

    return 0;
}

/*
Expected Output: 101515
Explanation: x=10 (lvalue), y=15 (from prvalue x+5), z=15 (xvalue reference to materialized temporary)
*/