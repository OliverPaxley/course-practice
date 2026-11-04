// value_categories.cpp
#include <iostream>
using namespace std;
void firstWalkthrogh() {
    cout << "First Walkthrough" << endl;
    int x = 10;          // x is an lvalue
    cout << x << endl;   // 'x' refers to a memory location

    int y = x + 5;       // (x + 5) is a prvalue
    cout << y << endl;

    int&& z = x + 5;     // result of (x + 5) materializes into an xvalue
    cout << z << endl;
}
void secondWalkthrough() {
    cout << "Second Walkthrough" << endl;
    int* a, b, c = 10, *p; // a and p are pointers, b and c are integers

    b = ((c += 5), cout << c << endl , 10);// c is 15 ane b is 10;

    for (int i = 0, j = 0; i < 10; cout << "hello", (i <= 8 ? cout << ", " : cout), j++, i++);
    cout << endl;
    // above is like line 5         above is like lik 7
}
void thirdWalkthrough(){
    cout << "Third Walkthrough" << endl;
    int a[5] = { 10, 20, 30, 40, 50 };
    int* p = &a[2];
    cout << "a[2] = " << a[2] << " or " << *(a + 2) << endl;
    cout << "a[0] = " << p[-2] << " or " << *(p - 2) << endl;
}
void fourthWalkthrough() {
    cout << "Fourth Walkthrough" << endl;
    int x = 5;
    int a[20]{};
    int* p = a;
    cout << sizeof(int) << " " << sizeof(x) << endl;
    cout << "Array size: " << sizeof(a) << " decayed to pointer: " << sizeof(p) << endl;
}
void fifthWalkthrough(){
    cout << "Fifth Walkthrough" << endl;
    int x = 0;
    cout << !x << endl;   // true (1), since x == 0
    x = 5;
    cout << !x << endl;   // false (0), since x != 0
    cout << !!x << endl;  // true (1), since x = 5;
}
void sixthWalkthrough(){
    cout << "Sixth Walkthrough" << endl;
    int i = 0;
    if (i != 0 && (i+=10))  // second part not evaluated
        cout << "Won't crash" << endl;
    else 
        cout << "Safe!" << endl;
    cout << i << endl;
    int a[50]{};
    // say the array has values
    int cnt{};
    for (int i = 0; i < 50; i++) {
        (a[i] == 10) && (cnt+=1);
    }
}

void seventhWalkthrough(){
    cout << "Seventh Walkthrough" << endl;
    int x = -10;
    int sign = (x < 0 ? -1 : 1);
    cout << "sign = " << sign << endl;
}
size_t recursiveEx(size_t num) {
    if (num <= 2) return num;
    else return num * recursiveEx(num - 1);
}
int main() {
    firstWalkthrogh();
    secondWalkthrough();
    thirdWalkthrough();
    fourthWalkthrough();
    fifthWalkthrough();
    sixthWalkthrough();
    seventhWalkthrough();
    cout << "Recursive Example" << endl;
    cout << recursiveEx(4) << endl;
    return 0;
}