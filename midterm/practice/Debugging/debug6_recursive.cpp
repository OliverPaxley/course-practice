// Debugging Practice 6 - Recursive Function
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

size_t recursiveEx(size_t num) {
    if (num <= 2) return num;
    else return num * recursiveEx(num - 1);
}

int main() {
    cout << recursiveEx(4);
    return 0;
}

/*
Expected Output: 24
Explanation: recursiveEx(4) = 4 * recursiveEx(3) = 4 * (3 * recursiveEx(2)) = 4 * 3 * 2 = 24
Wait: base case is num <= 2 returns num, so recursiveEx(2) = 2, recursiveEx(3) = 3 * 2 = 6, recursiveEx(4) = 4 * 6 = 24
*/