#include <iostream>
using namespace std;

int main() {
    int a = 0; //static allocation
    int* b = new int(20); // dynamic allocation 

    cout << "A: " << a << ", B: " << *b << endl;

    delete b;
    b = nullptr;
    return 0;
}