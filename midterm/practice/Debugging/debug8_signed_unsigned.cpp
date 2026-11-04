// Debugging Practice 8 - Signed/Unsigned Comparison
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

int main() {
    unsigned len = 0;
    if (len > -1)
        cout << "True";
    else
        cout << "False";

    int signedLen = 0;
    if (signedLen > -1)
        cout << "True";
    else
        cout << "False";

    return 0;
}

/*
Expected Output: FalseTrue
Explanation: len is unsigned, -1 becomes 4294967295 (huge), so 0 > 4294967295 is False.
signedLen is signed, 0 > -1 is True.
*/