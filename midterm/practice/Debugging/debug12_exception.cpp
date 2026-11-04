// Debugging Practice 12 - Exception Handling
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>
#include <stdexcept>

using namespace std;

void func1() {
    throw runtime_error("Error1");
}

void func2() noexcept {
    func1();  // If func1 throws, terminate!
}

int main() {
    try {
        func1();
    } catch (const exception& e) {
        cout << "Caught:" << e.what();
    }
    return 0;
}

/*
Expected Output: Caught:Error1
Explanation: func1 throws, caught in main. func2 is never called.
Note: If func2 were called, it would terminate because noexcept function called throwing function.
*/