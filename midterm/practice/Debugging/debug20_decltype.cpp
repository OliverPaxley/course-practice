// Debugging Practice 20 - Structured Binding and Decltype
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>
#include <utility>

using namespace std;

int main() {
    int x = 10;
    int& ref = x;

    decltype(ref) a = x;      // int&
    decltype((x)) b = x;      // int& (parenthesized lvalue)
    decltype(x) c = x;        // int

    cout << a << b << c;

    // Structured binding (C++17)
    auto [d, e] = pair<int, double>(42, 3.14);
    cout << d << static_cast<int>(e);

    return 0;
}

/*
Expected Output: 101010423
Explanation: a=10 (int&), b=10 (int&), c=10 (int). d=42, e=3.14 (cast to int=3)
*/