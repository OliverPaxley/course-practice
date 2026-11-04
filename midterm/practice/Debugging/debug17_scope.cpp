// Debugging Practice 17 - Scope and Shadowing
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

int value = 100;  // Global

int main() {
    int value = 10;  // Shadows global
    cout << value;

    {
        int value = 5;  // Shadows outer
        cout << value;
    }

    cout << value;  // Back to local (10)
    cout << ::value;  // Global (100)

    return 0;
}

/*
Expected Output: 10510100
Explanation: Local value=10, block value=5, after block back to 10, ::value=100
*/