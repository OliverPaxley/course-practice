// Fundamental Types - Practice Code for Midterm
// Topics: Integer types, floating-point types, boolean, character types, initialization, type inference, alignment

#include <iostream>
#include <cstdint>
#include <limits>
#include <type_traits>

using namespace std;

void integerTypes() {
    cout << "=== Integer Types ===" << endl;

    // Standard signed integers
    signed char sc = 'A';          // 1 byte, -128 to 127
    short int si = 32767;          // At least 16 bits
    int i = 2147483647;            // At least 32 bits
    long int li = 2147483647L;     // At least 32 bits
    long long int lli = 9223372036854775807LL; // At least 64 bits

    // Constant syntax
    int octal = 0133;              // Octal (starts with 0)
    int hex = 0x5b;                // Hexadecimal (starts with 0x)
    long int longHex = 0x5bL;
    long long int longLongHex = 0x5bLL;
    signed char charHex = '\x5b';  // Character hex

    // Unsigned integers
    unsigned char uc = 255;
    unsigned int ui = 4294967295U;
    unsigned long int uli = 4294967295UL;
    unsigned long long int ulli = 18446744073709551615ULL;

    cout << "Signed char range: " << static_cast<int>(numeric_limits<signed char>::min())
         << " to " << static_cast<int>(numeric_limits<signed char>::max()) << endl;
    cout << "Int range: " << numeric_limits<int>::min()
         << " to " << numeric_limits<int>::max() << endl;
    cout << "Unsigned int max: " << numeric_limits<unsigned int>::max() << endl;
}

void floatingPointTypes() {
    cout << "\n=== Floating-Point Types ===" << endl;

    float f = 3.14159f;            // 4 bytes, ~6 significant digits
    double d = 3.141592653589793;  // 8 bytes, ~15 significant digits
    long double ld = 3.14159265358979323846L; // At least 8 bytes

    cout << "Float: " << f << ", size: " << sizeof(f) << " bytes" << endl;
    cout << "Double: " << d << ", size: " << sizeof(d) << " bytes" << endl;
    cout << "Long double: " << ld << ", size: " << sizeof(ld) << " bytes" << endl;

    // IEEE 754 limits
    cout << "Float max: " << numeric_limits<float>::max() << endl;
    cout << "Double max: " << numeric_limits<double>::max() << endl;
}

void booleanAndCharacterTypes() {
    cout << "\n=== Boolean and Character Types ===" << endl;

    bool b = true;                 // 1 byte
    char c = 'A';                  // UTF-8, basic execution character set
    signed char sc = 'A';
    unsigned char uc = 'A';
    wchar_t wc = L'广';            // Wide character
    char16_t c16 = u'广';          // UTF-16
    char32_t c32 = U'广';          // UTF-32

    cout << "Bool size: " << sizeof(b) << endl;
    cout << "Char size: " << sizeof(c) << endl;
    cout << "wchar_t size: " << sizeof(wc) << endl;
    cout << "char16_t size: " << sizeof(c16) << endl;
    cout << "char32_t size: " << sizeof(c32) << endl;
}

void initializationForms() {
    cout << "\n=== Initialization Forms ===" << endl;

    // C-style copy initialization
    int n0 = 7;
    int n1 = 7.2;                  // Narrowing conversion (loses information)

    // Universal initialization (braces) - RECOMMENDED
    int n2 {6};                    // Direct-list initialization
    int n3 = {5};                  // Copy-list initialization
    int n4 {};                     // Value initialization (zero)
    int n5 = {};                   // Value initialization (zero)

    // Narrowing prevention with braces
    // int n6 {7.2};               // ERROR: narrowing conversion
    // int n7 = {7.2};             // ERROR: narrowing conversion

    cout << "n0 (C-style): " << n0 << endl;
    cout << "n1 (narrowing): " << n1 << endl;  // Outputs 7
    cout << "n2 (braces): " << n2 << endl;
    cout << "n3 (copy braces): " << n3 << endl;
    cout << "n4 (value init): " << n4 << endl;
    cout << "n5 (value init): " << n5 << endl;
}

void typeInference() {
    cout << "\n=== Type Inference (auto) ===" << endl;

    auto a = 42;                   // int
    auto b = 3.14;                 // double
    auto c = 'A';                  // char
    auto d = "Hello";              // const char*
    auto e = true;                 // bool

    const auto f = 100;            // const int
    auto& ref = a;                 // int&
    const auto& cref = b;          // const double&

    // Range-based for with auto
    int arr[]{1, 2, 3, 4, 5};
    for (auto& x : arr) { x *= 2; } // Modify elements

    // Cannot use auto for array top-level
    // auto arr2[] = {1, 2, 3};    // ERROR

    cout << "a (int): " << a << endl;
    cout << "b (double): " << b << endl;
    cout << "c (char): " << c << endl;
    cout << "d (const char*): " << d << endl;
    cout << "e (bool): " << e << endl;
    cout << "f (const int): " << f << endl;
}

void alignment() {
    cout << "\n=== Type Alignment ===" << endl;

    struct A { int n; char c; };           // alignof(A) = 4 (typical)
    struct alignas(16) B { int n; char c; }; // alignof(B) = 16

    cout << "alignof(int): " << alignof(int) << endl;
    cout << "alignof(double): " << alignof(double) << endl;
    cout << "alignof(A): " << alignof(A) << endl;
    cout << "alignof(B): " << alignof(B) << endl;
    cout << "alignof(max_align_t): " << alignof(max_align_t) << endl;
}

void signedUnsignedTrap() {
    cout << "\n=== Signed/Unsigned Comparison Trap ===" << endl;

    unsigned int len = 0u;

    // DANGER: Signed promoted to unsigned!
    if (len > -1) {
        cout << "len > -1 is TRUE (but -1 becomes 4294967295!)" << endl;
    } else {
        cout << "len > -1 is FALSE (correct behavior)" << endl;
    }

    // Safe comparison
    if (len > static_cast<unsigned int>(-1)) {
        cout << "With cast: TRUE" << endl;
    } else {
        cout << "With cast: FALSE" << endl;
    }

    // Better: use signed for comparisons
    int signedLen = 0;
    if (signedLen > -1) {
        cout << "Signed comparison: TRUE" << endl;
    }
}

void twoComplement() {
    cout << "\n=== Two's Complement ===" << endl;

    // Two's complement: invert bits and add 1
    signed char x = 5;       // 00000101
    signed char neg_x = -x;  // 11111011 = -5

    cout << "5: " << static_cast<int>(x) << endl;
    cout << "-5: " << static_cast<int>(neg_x) << endl;
    cout << "~5 + 1: " << static_cast<int>(~x + 1) << endl;

    // Unsigned negation: 2^n - value
    unsigned int u = 2;
    cout << "-2u = " << -u << " (2^32 - 2 = 4294967294)" << endl;
    cout << "-1u = " << -1u << " (2^32 - 1 = 4294967295)" << endl;
    cout << "-0u = " << -0u << endl;
}

int main() {
    integerTypes();
    floatingPointTypes();
    booleanAndCharacterTypes();
    initializationForms();
    typeInference();
    alignment();
    signedUnsignedTrap();
    twoComplement();

    return 0;
}