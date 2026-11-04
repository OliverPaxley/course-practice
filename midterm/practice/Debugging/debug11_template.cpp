// Debugging Practice 11 - Template Specialization
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

template <typename T>
void print(T value) {
    cout << "General:" << value;
}

template <>
void print<int>(int value) {
    cout << "Int:" << value * 2;
}

int main() {
    print(3.14);
    print(5);
    return 0;
}

/*
Expected Output: General:3.14Int:10
Explanation: print(3.14) uses general template, print(5) uses int specialization
*/