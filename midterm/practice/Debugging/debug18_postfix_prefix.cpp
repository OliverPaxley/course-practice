// Debugging Practice 18 - Postfix vs Prefix
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

int main() {
    int x = 5;
    cout << x++;  // Postfix: returns 5, then x=6
    cout << x;    // x is now 6

    int y = 5;
    cout << ++y;  // Prefix: y=6, returns 6
    cout << y;    // y is 6

    return 0;
}

/*
Expected Output: 5666
Explanation: x++ returns 5, then x=6. ++y makes y=6 then returns 6.
*/