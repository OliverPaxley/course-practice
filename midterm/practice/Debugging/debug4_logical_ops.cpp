// Debugging Practice 4 - Logical Operators and Short-Circuit
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

int main() {
    int i = 0;
    if (i != 0 && (i += 10))
        cout << "Wont crash";
    else
        cout << "Safe";
    cout << i;

    int a[50]{};
    int cnt{};
    for (int i = 0; i < 50; i++) {
        (a[i] == 10) && (cnt += 1);
    }
    cout << cnt;

    return 0;
}

/*
Expected Output: Safe00
Explanation: i=0, so i!=0 is false, short-circuit prevents i+=10, outputs "Safe" then i=0.
Loop: a[i] is 0 (default initialized), so a[i]==10 is false, short-circuit prevents cnt+=1, cnt stays 0.
*/