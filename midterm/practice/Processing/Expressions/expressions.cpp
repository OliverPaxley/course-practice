// Expressions - Practice Code for Midterm
// Topics: Value categories, operator precedence, postfix/prefix expressions,
// unary/binary/ternary expressions, short-circuit evaluation, mixed-type expressions

#include <iostream>
#include <type_traits>

using namespace std;

// ============================================
// VALUE CATEGORIES
// ============================================

void valueCategories() {
    cout << "=== Value Categories ===" << endl;

    int x = 10;              // x is an lvalue
    int y = x + 5;           // (x + 5) is a prvalue
    int&& z = x + 5;         // Result materializes into xvalue

    cout << "x (lvalue): " << x << endl;
    cout << "y (from prvalue): " << y << endl;
    cout << "z (xvalue ref): " << z << endl;

    // lvalue operands include:
    // - Name that is not an array name
    // - Array element: a[i]
    // - Parenthesized lvalue: (expression)
    // - Direct member selection: expression.member
    // - Indirect member selection: expression->member
    // - Dereferenced address: *expression
    // - String literal

    int arr[3] = {1, 2, 3};
    int* p = arr;
    cout << "arr[1] (lvalue): " << arr[1] << endl;
    cout << "*p (lvalue): " << *p << endl;

    // Operators requiring lvalue operands:
    // Address-of: &
    // Prefix/postfix ++/--
    // Assignment operators (left operand): =, +=, -=, *=, /=, %=

    int a = 5;
    int* ptr = &a;           // & requires lvalue
    ++a;                     // Prefix ++ requires lvalue
    a++;                     // Postfix ++ requires lvalue
    a += 3;                  // += requires lvalue
}

// ============================================
// OPERATOR PRECEDENCE
// ============================================

void operatorPrecedence() {
    cout << "\n=== Operator Precedence ===" << endl;

    // Highest to lowest (key levels):
    // 17: Postfix: [] () . -> ++ --
    // 16: Prefix/Unary: ++ -- sizeof ! ~ - + & * new delete
    // 14: Multiplicative: * / %
    // 13: Additive: + -
    // 12: Shift: << >>
    // 11: Relational: < > <= >=
    // 10: Equality: == !=
    // 9: Bitwise AND: &
    // 8: Bitwise XOR: ^
    // 7: Bitwise OR: |
    // 6: Logical AND: &&
    // 5: Logical OR: ||
    // 4: Ternary: ?:
    // 3: Assignment: = += -= *= /= %= (right-to-left)
    // 1: Comma: , (left-to-right)

    int result = 2 + 3 * 4;  // * higher than +, so 2 + 12 = 14
    cout << "2 + 3 * 4 = " << result << endl;

    result = (2 + 3) * 4;    // Parentheses override: 5 * 4 = 20
    cout << "(2 + 3) * 4 = " << result << endl;

    int i = 5;
    result = i++ + i++;      // UNDEFINED! Order of evaluation unspecified
    cout << "i++ + i++ = " << result << " (UNDEFINED BEHAVIOR)" << endl;

    // Better: separate statements
    i = 5;
    int temp1 = i++;
    int temp2 = i++;
    result = temp1 + temp2;
    cout << "Sequential: " << result << endl;
}

// ============================================
// POSTFIX EXPRESSIONS
// ============================================

void postfixExpressions() {
    cout << "\n=== Postfix Expressions ===" << endl;

    // Subscripting []
    int arr[5] = {10, 20, 30, 40, 50};
    int* p = arr;
    cout << "arr[2] = " << arr[2] << endl;
    cout << "p[2] = " << p[2] << endl;
    cout << "*(p+2) = " << *(p+2) << endl;
    cout << "p[-1] = " << p[-1] << " (if p points to arr[1])" << endl;

    // Member selection . and ->
    struct S { int x; };
    S s{42};
    S* sp = &s;
    cout << "s.x = " << s.x << endl;
    cout << "sp->x = " << sp->x << endl;

    // Postfix increment/decrement
    int val = 10;
    cout << "val++ = " << val++ << " (result is prvalue)" << endl;  // 10
    cout << "val after = " << val << endl;  // 11

    // ERROR: (val++)++  - val++ is prvalue, not lvalue
    // ++(val++)  - ERROR: val++ is prvalue

    // Unsigned limits
    unsigned u = 0;
    cout << "0u-- = " << u-- << endl;  // Wraps to max
    cout << "After: " << u << endl;

    unsigned maxU = 4294967295u;
    cout << "MAXu++ = " << maxU++ << endl;  // Wraps to 0
}

// ============================================
// PREFIX EXPRESSIONS
// ============================================

void prefixExpressions() {
    cout << "\n=== Prefix Expressions ===" << endl;

    int val = 10;
    cout << "++val = " << ++val << " (result is lvalue)" << endl;  // 11
    cout << "val after = " << val << endl;  // 11

    // Prefix returns lvalue, so can chain
    int x = 5;
    ++(++x);  // OK: (++x) is lvalue
    cout << "++(++x) = " << x << endl;  // 7

    // Postfix returns prvalue, cannot chain
    // (x++)++;  // ERROR: x++ is prvalue
}

// ============================================
// UNARY EXPRESSIONS
// ============================================

void unaryExpressions() {
    cout << "\n=== Unary Expressions ===" << endl;

    // sizeof
    int arr[10];
    int* ptr = arr;
    cout << "sizeof(arr) = " << sizeof(arr) << endl;     // 40 (10 * 4)
    cout << "sizeof(ptr) = " << sizeof(ptr) << endl;     // 8 (pointer size)
    cout << "sizeof(int) = " << sizeof(int) << endl;     // 4

    int j = 5;
    cout << "sizeof j++ = " << sizeof(j++) << endl;  // j NOT incremented!
    cout << "j after sizeof = " << j << endl;        // Still 5

    // Logical negation !
    cout << "!0 = " << !0 << endl;      // 1 (true)
    cout << "!5 = " << !5 << endl;      // 0 (false)
    cout << "!nullptr = " << !nullptr << endl;  // 1 (true)

    // Arithmetic negation -
    cout << "-5 = " << -5 << endl;
    cout << "-5u = " << -5u << endl;    // Unsigned: 2^32 - 5

    // Address-of &
    int a = 42;
    int* pa = &a;
    cout << "&a = " << pa << endl;

    // Indirection *
    cout << "*pa = " << *pa << endl;
    cout << "*&a = " << *&a << endl;    // Inverse of &

    // decltype
    int b = 10;
    int& ref = b;
    decltype(ref) c = b;   // c is int&
    decltype((b)) d = b;   // d is int& (parenthesized lvalue)
    cout << "decltype(ref): " << is_same_v<decltype(ref), int&> << endl;
    cout << "decltype((b)): " << is_same_v<decltype((b)), int&> << endl;

    // noexcept
    auto noThrow = []() noexcept { return 42; };
    auto mayThrow = []() { throw 1; };
    cout << "noexcept(noThrow()): " << noexcept(noThrow()) << endl;
    cout << "noexcept(mayThrow()): " << noexcept(mayThrow()) << endl;
}

// ============================================
// CONSTRAINED CASTS
// ============================================

void constrainedCasts() {
    cout << "\n=== Constrained Casts ===" << endl;

    double d_val = 3.14;
    int i = static_cast<int>(d_val);      // Standard conversion
    cout << "static_cast<int>(3.14) = " << i << endl;

    // const_cast - remove const
    const int ci = 42;
    int* nonConst = const_cast<int*>(&ci);
    // *nonConst = 100;  // UNDEFINED BEHAVIOR!

    // reinterpret_cast - low-level reinterpretation
    int val = 0x41424344;
    char* bytes = reinterpret_cast<char*>(&val);
    cout << "reinterpret_cast bytes: " << bytes[0] << bytes[1] << bytes[2] << bytes[3] << endl;

    // dynamic_cast - requires polymorphic type
    struct Base { virtual ~Base() = default; };
    struct Derived : Base { int x = 42; };

    Base* b = new Derived();
    Derived* d_ptr = dynamic_cast<Derived*>(b);
    if (d_ptr) cout << "dynamic_cast succeeded: " << d_ptr->x << endl;

    Base* b2 = new Base();
    Derived* d2 = dynamic_cast<Derived*>(b2);
    if (!d2) cout << "dynamic_cast failed (nullptr)" << endl;

    delete b;
    delete b2;
}

// ============================================
// BINARY EXPRESSIONS
// ============================================

void binaryExpressions() {
    cout << "\n=== Binary Expressions ===" << endl;

    // Arithmetic
    cout << "10 + 3 = " << 10 + 3 << endl;
    cout << "10 - 3 = " << 10 - 3 << endl;
    cout << "10 * 3 = " << 10 * 3 << endl;
    cout << "10 / 3 = " << 10 / 3 << endl;      // Integer division
    cout << "10 % 3 = " << 10 % 3 << endl;

    // Relational
    cout << "10 > 3: " << (10 > 3) << endl;
    cout << "10 == 3: " << (10 == 3) << endl;

    // Logical with SHORT-CIRCUIT EVALUATION
    int x = 0;
    // Order matters!
    if (x != 0 && 10 / x > 2) {  // SAFE: right side not evaluated
        cout << "Won't execute" << endl;
    }

    // DANGEROUS ORDER:
    // if (10 / x > 2 && x != 0)  // CRASH: division by zero!

    // Assignment
    int a = 1, b = 2, c = 3;
    a = b = c = 4;  // Right-to-left: a = (b = (c = 4))
    cout << "a=b=c=4: a=" << a << ", b=" << b << ", c=" << c << endl;

    // Compound assignment
    a = 10;
    a += 5;  // a = a + 5
    cout << "a += 5: " << a << endl;

    // Comma operator
    int result = (a = 5, b = 10, a + b);  // Evaluates left-to-right, result is rightmost
    cout << "Comma: (a=5, b=10, a+b) = " << result << endl;
}

// ============================================
// MIXED-TYPE EXPRESSIONS
// ============================================

void mixedTypeExpressions() {
    cout << "\n=== Mixed-Type Expressions ===" << endl;

    // Promotion hierarchy (highest to lowest):
    // long double -> double -> float -> unsigned long long -> long long
    // -> unsigned long -> long -> unsigned int -> int -> unsigned char -> char -> bool

    int i = 10;
    unsigned u = 20;
    double d = 3.14;

    // int + unsigned -> unsigned
    cout << "i + u = " << i + u << " (type: unsigned)" << endl;

    // int + double -> double
    cout << "i + d = " << i + d << " (type: double)" << endl;

    // UNSIGNED TRAP
    unsigned len = 0;
    // len > -1  ->  len > 4294967295u  ->  FALSE!
    if (len > -1) {
        cout << "len > -1 is TRUE (WRONG!)" << endl;
    } else {
        cout << "len > -1 is FALSE (correct, -1 becomes huge unsigned)" << endl;
    }

    // Safe comparison
    if (len > static_cast<unsigned>(-1)) {  // Always false for valid lengths
        cout << "With cast" << endl;
    }

    // Better: use signed for comparisons
    int signedLen = 0;
    if (signedLen > -1) {
        cout << "Signed comparison works" << endl;
    }
}

// ============================================
// TERNARY EXPRESSION
// ============================================

void ternaryExpressions() {
    cout << "\n=== Ternary Expression ===" << endl;

    int x = 5;
    int sign = (x < 0) ? -1 : 1;
    cout << "sign of 5: " << sign << endl;

    x = -3;
    sign = (x < 0) ? -1 : 1;
    cout << "sign of -3: " << sign << endl;

    // Low precedence - usually needs parentheses
    int a = 10, b = 20;
    int max = (a > b) ? a : b;
    cout << "max(10, 20) = " << max << endl;

    // Only one operand evaluated
    int y = 0;
    int z = (y != 0) ? (10 / y) : 0;  // Safe: 10/y not evaluated
    cout << "Safe division: " << z << endl;
}

// ============================================
// EXPRESSION EVALUATION ORDER
// ============================================

void evaluationOrder() {
    cout << "\n=== Evaluation Order ===" << endl;

    // Order of operand evaluation is UNSPECIFIED (except &&, ||, ,, ?:)
    int i = 5;
    // int result = f(i++) + g(i++);  // UNDEFINED: which i++ first?

    // Function calls: order of argument evaluation unspecified
    // auto print = [](int v) { cout << v << ' '; return v; };
    // print(i++) + print(i++);  // Unspecified order

    // Safe: separate statements
    i = 5;
    int a = i++;  // a = 5, i = 6
    int b = i++;  // b = 6, i = 7
    cout << "Sequential: a=" << a << ", b=" << b << endl;

    // GUARANTEED ORDER:
    // && left-to-right, short-circuit
    // || left-to-right, short-circuit
    // , left-to-right
    // ?: condition first, then chosen operand
}

int main() {
    valueCategories();
    operatorPrecedence();
    postfixExpressions();
    prefixExpressions();
    unaryExpressions();
    constrainedCasts();
    binaryExpressions();
    mixedTypeExpressions();
    ternaryExpressions();
    evaluationOrder();

    return 0;
}