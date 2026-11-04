// Functions - Practice Code for Midterm
// Topics: Function syntax, trailing return type, linkage, recursion, function pointers,
// function objects (functors), lambda expressions

#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

// ============================================
// TRAILING RETURN TYPE
// ============================================

// C++11 trailing return type syntax
auto add(int a, int b) -> int {
    return a + b;
}

// Use case 1: Return type defined in class scope
class Ticket {
    enum class Type { Adult, Child, Senior };
public:
    auto getType() const -> Type { return Type::Adult; }
};

// Use case 2: Template return type depends on parameters
template <typename T, typename U>
auto multiply(T a, U b) -> decltype(a * b) {
    return a * b;
}

// ============================================
// LINKAGE
// ============================================

// External linkage (default) - visible outside translation unit
void externalFunction() {
    cout << "External linkage" << endl;
}

// Internal linkage - only visible in this translation unit
static void internalFunction() {
    cout << "Internal linkage" << endl;
}

// In header files, use anonymous namespace for internal linkage
namespace {
    void anonymousNamespaceFunction() {
        cout << "Anonymous namespace (internal linkage)" << endl;
    }
}

// ============================================
// RECURSION
// ============================================

unsigned long long factorial(unsigned n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

// Tail recursion (optimizable)
unsigned long long factorialTail(unsigned n, unsigned long long acc = 1) {
    return (n <= 1) ? acc : factorialTail(n - 1, n * acc);
}

// Fibonacci (exponential without memoization)
unsigned long long fibonacci(unsigned n) {
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

// Iterative alternative (better for stack)
unsigned long long fibonacciIter(unsigned n) {
    if (n <= 1) return n;
    unsigned long long a = 0, b = 1;
    for (unsigned i = 2; i <= n; ++i) {
        unsigned long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

void recursionDemo() {
    cout << "=== Recursion ===" << endl;
    cout << "factorial(5) = " << factorial(5) << endl;
    cout << "factorialTail(5) = " << factorialTail(5) << endl;
    cout << "fibonacci(10) = " << fibonacci(10) << endl;
    cout << "fibonacciIter(10) = " << fibonacciIter(10) << endl;
}

// ============================================
// FUNCTION POINTERS
// ============================================

// Function pointer type
using CompareFunc = bool(*)(int, int);

bool ascending(int a, int b) { return a < b; }
bool descending(int a, int b) { return a > b; }

// Function taking function pointer
void sortArray(int* arr, size_t n, CompareFunc comp) {
    for (size_t i = 0; i < n - 1; ++i) {
        for (size_t j = 0; j < n - i - 1; ++j) {
            if (comp(arr[j], arr[j + 1])) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Array of function pointers
CompareFunc criteria[2] = {ascending, descending};

void functionPointerDemo() {
    cout << "\n=== Function Pointers ===" << endl;

    int arr[] = {5, 2, 8, 1, 9};
    size_t n = 5;

    cout << "Original: ";
    for (int x : arr) cout << x << ' ';
    cout << endl;

    sortArray(arr, n, ascending);
    cout << "Ascending: ";
    for (int x : arr) cout << x << ' ';
    cout << endl;

    sortArray(arr, n, descending);
    cout << "Descending: ";
    for (int x : arr) cout << x << ' ';
    cout << endl;

    // Array of function pointers
    cout << "Using array[0] (ascending): " << criteria[0](3, 5) << endl;
    cout << "Using array[1] (descending): " << criteria[1](3, 5) << endl;
}

// ============================================
// FUNCTION OBJECTS (FUNCTORS)
// ============================================

// Functor class - can maintain state!
template <typename T>
class Comparator {
    bool ascending;
    size_t callCount = 0;  // State!
public:
    Comparator(bool asc = true) : ascending(asc) {}

    bool operator()(const T& a, const T& b) {
        ++callCount;
        return ascending ? a < b : a > b;
    }

    size_t getCallCount() const { return callCount; }
    void resetCount() { callCount = 0; }
};

// Functor with captured configuration
class Multiplier {
    int factor;
public:
    Multiplier(int f) : factor(f) {}
    int operator()(int x) const { return x * factor; }
};

void functorDemo() {
    cout << "\n=== Function Objects (Functors) ===" << endl;

    Comparator<int> comp(true);
    vector<int> vec = {5, 2, 8, 1, 9};

    sort(vec.begin(), vec.end(), comp);
    cout << "Sorted ascending: ";
    for (int x : vec) cout << x << ' ';
    cout << "\nComparator called " << comp.getCallCount() << " times" << endl;

    // Stateful functor
    Multiplier by3(3);
    cout << "by3(5) = " << by3(5) << endl;
    cout << "by3(10) = " << by3(10) << endl;

    // Use with algorithms
    vector<int> nums = {1, 2, 3, 4, 5};
    transform(nums.begin(), nums.end(), nums.begin(), by3);
    cout << "Multiplied by 3: ";
    for (int x : nums) cout << x << ' ';
    cout << endl;
}

// ============================================
// LAMBDA EXPRESSIONS
// ============================================

void lambdaBasics() {
    cout << "\n=== Lambda Basics ===" << endl;

    // Basic lambda
    auto hello = []() { return "Hello Lambda"; };
    cout << hello() << endl;

    // With parameters
    auto add = [](int a, int b) { return a + b; };
    cout << "add(3, 4) = " << add(3, 4) << endl;

    // Explicit return type (needed for complex returns)
    auto divide = [](int a, int b) -> double {
        return b != 0 ? static_cast<double>(a) / b : 0.0;
    };
    cout << "divide(10, 4) = " << divide(10, 4) << endl;
}

void lambdaCapture() {
    cout << "\n=== Lambda Capture ===" << endl;

    int x = 10, y = 20;

    // Capture by value
    auto byValue = [x, y]() { return x + y; };
    cout << "byValue: " << byValue() << endl;

    x = 100;  // Change after capture
    cout << "byValue after x=100: " << byValue() << endl;  // Still 30

    // Capture by reference
    auto byRef = [&x, &y]() { return x + y; };
    cout << "byRef: " << byRef() << endl;  // 120

    // Capture all by value
    auto allByValue = [=]() { return x + y; };

    // Capture all by reference
    auto allByRef = [&]() { return x + y; };

    // Mixed capture
    auto mixed = [=, &y]() { return x + y; };  // x by value, y by reference

    // Capture this
    struct Adder {
        int base = 100;
        auto makeAdder() { return [this](int x) { return base + x; }; }
    };

    Adder adder;
    auto add100 = adder.makeAdder();
    cout << "add100(5) = " << add100(5) << endl;
}

void lambdaMutable() {
    cout << "\n=== Mutable Lambdas ===" << endl;

    int counter = 0;

    // By default, captured by value are const
    // auto bad = [counter]() { return ++counter; };  // ERROR: counter is const

    // mutable allows modification of captured by value
    auto counterLambda = [counter]() mutable { return ++counter; };
    cout << "counterLambda(): " << counterLambda() << endl;  // 1
    cout << "counterLambda(): " << counterLambda() << endl;  // 2
    cout << "counterLambda(): " << counterLambda() << endl;  // 3
    cout << "Original counter: " << counter << endl;  // Still 0!

    // Capture by reference doesn't need mutable
    auto refCounter = [&counter]() { return ++counter; };
    cout << "refCounter(): " << refCounter() << endl;  // 1
    cout << "Original counter: " << counter << endl;  // 1
}

void lambdaWithSTL() {
    cout << "\n=== Lambdas with STL ===" << endl;

    vector<int> vec = {5, 2, 8, 1, 9, 3, 7};

    // sort with lambda
    sort(vec.begin(), vec.end(), [](int a, int b) { return a > b; });
    cout << "Descending: ";
    for (int x : vec) cout << x << ' ';
    cout << endl;

    // find_if with lambda
    auto it = find_if(vec.begin(), vec.end(), [](int x) { return x > 5; });
    if (it != vec.end()) cout << "First > 5: " << *it << endl;

    // transform with lambda
    vector<int> doubled(vec.size());
    transform(vec.begin(), vec.end(), doubled.begin(), [](int x) { return x * 2; });
    cout << "Doubled: ";
    for (int x : doubled) cout << x << ' ';
    cout << endl;

    // for_each with lambda
    cout << "for_each: ";
    for_each(vec.begin(), vec.end(), [](int x) { cout << x << ' '; });
    cout << endl;
}

void lambdaGeneric() {
    cout << "\n=== Generic Lambdas (C++14) ===" << endl;

    // Auto parameters - template lambda
    auto genericAdd = [](auto a, auto b) { return a + b; };
    cout << "int: " << genericAdd(3, 4) << endl;
    cout << "double: " << genericAdd(3.14, 2.86) << endl;
    cout << "string: " << genericAdd(string("Hello"), string(" World")) << endl;

    // Generic lambda with capture
    auto makeMultiplier = [](auto factor) {
        return [factor](auto x) { return x * factor; };
    };

    auto times3 = makeMultiplier(3);
    cout << "times3(5) = " << times3(5) << endl;
    cout << "times3(2.5) = " << times3(2.5) << endl;
}

void lambdaInitCapture() {
    cout << "\n=== Init Capture (C++14) ===" << endl;

    // Move capture
    auto ptr = make_unique<int>(42);
    auto lambda = [p = move(ptr)]() {
        cout << "Captured unique_ptr: " << *p << endl;
    };
    lambda();
    // ptr is now nullptr (moved)

    // Arbitrary expression capture
    auto lambda2 = [x = 10 + 5]() { cout << "x = " << x << endl; };
    lambda2();
}

// ============================================
// STD::FUNCTION
// ============================================

void stdFunctionDemo() {
    cout << "\n=== std::function ===" << endl;

    // Can store any callable: function pointer, functor, lambda
    function<int(int, int)> func;

    func = [](int a, int b) { return a + b; };
    cout << "Lambda: " << func(3, 4) << endl;

    func = plus<int>();  // Functor from <functional>
    cout << "std::plus: " << func(3, 4) << endl;

    func = [](int a, int b) { return a * b; };
    cout << "Lambda multiply: " << func(3, 4) << endl;

    // Vector of functions
    vector<function<int(int)>> funcs = {
        [](int x) { return x * 2; },
        [](int x) { return x * 3; },
        [](int x) { return x * 4; }
    };

    for (const auto& f : funcs) {
        cout << "f(5) = " << f(5) << endl;
    }
}

// ============================================
// HIGHER-ORDER FUNCTIONS
// ============================================

// Function that takes function as parameter
template <typename Func>
void applyTwice(Func f, int& value) {
    f(value);
    f(value);
}

// Function that returns function
auto makeAdder(int x) {
    return [x](int y) { return x + y; };
}

// Function composition
template <typename F, typename G>
auto compose(F f, G g) {
    return [f, g](auto x) { return f(g(x)); };
}

void higherOrderDemo() {
    cout << "\n=== Higher-Order Functions ===" << endl;

    int value = 5;
    applyTwice([](int& v) { v *= 2; }, value);
    cout << "After applyTwice(*2): " << value << endl;  // 20

    auto add5 = makeAdder(5);
    cout << "add5(10) = " << add5(10) << endl;  // 15

    auto add1 = [](int x) { return x + 1; };
    auto mul2 = [](int x) { return x * 2; };
    auto add1ThenMul2 = compose(mul2, add1);
    cout << "compose(mul2, add1)(5) = " << add1ThenMul2(5) << endl;  // (5+1)*2 = 12
}

int main() {
    // Trailing return type
    cout << "add(3, 4) = " << add(3, 4) << endl;
    cout << "multiply(3, 4.5) = " << multiply(3, 4.5) << endl;

    // Linkage
    externalFunction();
    internalFunction();
    anonymousNamespaceFunction();

    // Recursion
    recursionDemo();

    // Function pointers
    functionPointerDemo();

    // Functors
    functorDemo();

    // Lambdas
    lambdaBasics();
    lambdaCapture();
    lambdaMutable();
    lambdaWithSTL();
    lambdaGeneric();
    lambdaInitCapture();

    // std::function
    stdFunctionDemo();

    // Higher-order functions
    higherOrderDemo();

    return 0;
}