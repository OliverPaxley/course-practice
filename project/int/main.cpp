#include "int.h"
using namespace std;
int main() {
    // The constructor initializes an Int; its default value is 0.
    Int mark;

    cout << "Enter a mark (0-100): ";

    // Exercise the overloaded input operator (which calls Int::get(istream&)).
    cin >> mark;

    // Exercise the overloaded output operator (which calls Int::put(ostream&)).
    cout << "Mark entered: " << mark << '\n';

    // Also demonstrate calling the public member functions directly.
    cout << "Enter another mark (0-100): ";
    mark.get(cin);
    cout << "Second mark: ";
    mark.put(cout) << '\n';

    return 0;
}
