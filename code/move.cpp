#include <iostream>
#include "IntArray.h"
using namespace std;
using namespace seneca;
//void print(IntArray I) {
//   for (size_t i = 0; i < I.size(); i++) {
//      cout << I[i];
//      if (i != I.size()-1) cout << ", ";
//   }
//   cout << endl;
//}
void print(IntArray&& I) {
   for (size_t i = 0; i < I.size(); i++) {
      cout << I[i];
      if (i != I.size() - 1) cout << ", ";
   }
   cout << endl;
}
int main() {
   cout << "OOP345 NAA - Sep 21" << endl;
   IntArray I(5);
   for (size_t i = 1; i <= 5; i++) {
      I[i - 1] = i * 10;
   }
   print(std::move(I));

   return 0;
}