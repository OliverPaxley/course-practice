// Debugging Practice 19 - Enum Class
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

enum Color { RED, GREEN, BLUE };
enum class ColorClass { RED, GREEN, BLUE };

int main() {
    Color c1 = RED;
    ColorClass c2 = ColorClass::RED;

    cout << c1 << static_cast<int>(c2);

    return 0;
}

/*
Expected Output: 00
Explanation: Plain enum RED=0, scoped enum ColorClass::RED=0 (cast to int for output)
*/