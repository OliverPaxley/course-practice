// Debugging Practice 13 - Static Members and Constexpr
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

class Counter {
    static int count;
public:
    Counter() { ++count; }
    static int getCount() { return count; }
};

int Counter::count = 0;

constexpr int compute(int n) {
    return n * 2;
}

int main() {
    Counter c1, c2;
    cout << Counter::getCount() << compute(5);
    return 0;
}

/*
Expected Output: 210
Explanation: Two Counter objects created, count=2. compute(5) = 10 at compile time.
*/