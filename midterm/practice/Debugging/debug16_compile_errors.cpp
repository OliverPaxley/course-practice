// Debugging Practice 16 - Fails to Compile Examples
// Predict: "Fails to Compile"

#include <iostream>

using namespace std;

int main() {
    // ERROR: Reference must be initialized
    // int& ref;

    // ERROR: Array of references not allowed
    // int& arr[3];

    // ERROR: Pointer to reference not allowed
    // int&* ptr;

    // ERROR: auto for array top-level
    // auto arr[] = {1, 2, 3};

    // ERROR: Narrowing with braces
    // int x{3.14};

    cout << "If you see this, the errors were commented out";
    return 0;
}

/*
Expected Output: If you see this, the errors were commented out
Explanation: All errors are commented out. Uncomment any to see "Fails to Compile"
*/