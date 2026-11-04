// Debugging Practice 2 - Pointer Arithmetic and Array Decay
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

int main() {
    int a[5] = {10, 20, 30, 40, 50};
    int* p = &a[2];
    cout << a[2] << *(a + 2) << p[-2] << *(p - 2);

    return 0;
}

/*
Expected Output: 30301010
Explanation: a[2]=30, *(a+2)=30, p[-2]=a[0]=10, *(p-2)=a[0]=10
*/