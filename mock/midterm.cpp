#include <iostream>
#include "midterm.h"
using namespace std;

int main(void) {
    int data[] = {3, 8, 15, 22, 7, 40, 11};

    int primeCount = seneca::countIf(data, 7, seneca::isPrime);

    int result[7]{};
    int resultCount = seneca::filter(data, 7, result,
        [](int x) { return x > 10; });

    cout << "Prime count: " << primeCount << endl;
    cout << "Values greater than 10:";
    for (int i = 0; i < resultCount; ++i) {
        cout << ' ' << result[i];
    }
    cout << endl;

    // A capturing lambda cannot convert to a plain function pointer because it
    // carries the captured limit value in its closure object.

    return 0;
}
