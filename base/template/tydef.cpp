#include <iostream>
using namespace std;

typedef const double ConstDouble; // basic allias
using number = int; // updated alias for modern C++
using dblePtr = double*; // updated alias pointer for modern C++.

int main() {
    // example of using the modern alias and the basic alias
    // basic 
    ConstDouble pi = 3.14;
    // modern alias
    number x = 5;
    number y = 52;

    number sum = x + y;

    cout << "Sum : " << sum << endl;
    // example of when to use the double pointer alias and why; 

    int* a, b; // a is a pointer and b is a double;
    dblePtr i, j; // i and j is a double;
    return 0;
}