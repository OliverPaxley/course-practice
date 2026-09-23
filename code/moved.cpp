#include <iostream>
#include "IntArray.h"
using namespace std;
using namespace seneca;
void print(const IntArray& I) {
    if (I.isEmpty()) { 
        cout << "Empty Array";
    }
    for (size_t i = 0; i < I.size(); i++) {
        cout << I[i];
        if (i != I.size() - 1) {
            cout << " , ";
        }
    }
   cout << endl;
}
int main() {
   cout << "OOP345 NAA - Sep 21" << endl;
   IntArray I(5);
    for (size_t i = 1; i <= 5; i++) {
        I[i - 1] = i * 10;
    }
   print(I);
   IntArray J(std::move(I));
   print(I);
   print(J);
   I = std::move(J);
   print(I);
   print(J);
   return 0;
}