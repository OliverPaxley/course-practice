// Debugging Practice 7 - Initialization and Narrowing
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

int main() {
    int n0 = 7;
    int n1 = 7.2;
    int n2{6};
    int n3 = {5};
    cout << n0 << n1 << n2 << n3;

    // int n4{7.2};  // Would fail to compile - narrowing
    // int n5 = {7.2};  // Would fail to compile - narrowing

    return 0;
}

/*
Expected Output: 7765
Explanation: n0=7 (C-style), n1=7 (narrowing 7.2->7), n2=6 (braces), n3=5 (copy braces)
*/