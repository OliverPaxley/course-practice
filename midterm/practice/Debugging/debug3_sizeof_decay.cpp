// Debugging Practice 3 - sizeof and Array Decay
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

void func(int arr[]) {
    // Array decays to pointer in function parameter
    cout << sizeof(arr);
}

int main() {
    int x = 5;
    int a[20]{};
    int* p = a;
    cout << sizeof(int) << sizeof(x) << sizeof(a) << sizeof(p);
    func(a);

    return 0;
}

/*
Expected Output: 448088
Explanation: sizeof(int)=4, sizeof(x)=4, sizeof(a)=80 (20*4), sizeof(p)=8 (pointer), func gets pointer so sizeof(arr)=8
Note: Actual pointer size depends on platform (8 on 64-bit, 4 on 32-bit)
*/