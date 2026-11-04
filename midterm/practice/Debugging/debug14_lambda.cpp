// Debugging Practice 14 - Lambda Captures
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

int main() {
    int x = 10, y = 20;

    auto byValue = [x, y]() { return x + y; };
    x = 100;
    cout << byValue();

    auto byRef = [&x, &y]() { return x + y; };
    cout << byRef();

    return 0;
}

/*
Expected Output: 30120
Explanation: byValue captures x=10, y=20 by value, so returns 30 even after x changes.
byRef captures by reference, so after x=100, returns 120.
*/