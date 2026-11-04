// Compilation and Execution - Practice Code for Midterm
// Topics: Compilation process, compiler options, main() prototypes,
// command-line arguments, constexpr, static_assert

#include <iostream>
#include <cstdlib>

using namespace std;

// ============================================
// CONSTANT EXPRESSIONS (constexpr)
// ============================================

constexpr int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr int fibonacci(int n) {
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

// constexpr variables
constexpr int MAX_SIZE = 100;
constexpr double PI = 3.14159265359;

// constexpr function with pointer
constexpr int* getPtr(int* p) { return p; }

void constexprDemo() {
    cout << "=== constexpr ===" << endl;

    // Compile-time evaluation
    constexpr int fact5 = factorial(5);   // 120
    constexpr int fib10 = fibonacci(10);  // 55

    cout << "factorial(5) = " << fact5 << endl;
    cout << "fibonacci(10) = " << fib10 << endl;
    cout << "MAX_SIZE = " << MAX_SIZE << endl;
    cout << "PI = " << PI << endl;

    // constexpr array size
    int arr[MAX_SIZE];  // OK: MAX_SIZE is constexpr

    // constexpr pointer
    int value = 42;
    constexpr int* ptr = getPtr(&value);
    cout << "*ptr = " << *ptr << endl;

    // Can only use constexpr in constant expressions
    // int runtime = 5;
    // constexpr int bad = factorial(runtime);  // ERROR: not constant expression
}

// ============================================
// STATIC ASSERTIONS
// ============================================

// Compile-time checks with custom messages
static_assert(sizeof(int) >= 4, "int must be at least 4 bytes");
static_assert(sizeof(double) == 8, "double must be 8 bytes");
static_assert(alignof(double) >= 8, "double alignment must be at least 8");

// Template static_assert
template <typename T>
class Container {
    static_assert(std::is_default_constructible_v<T>,
                  "T must be default constructible");
    static_assert(sizeof(T) <= 64,
                  "T must be small enough");
public:
    T data;
};

// Conditional static_assert
#define MY_ASSERT(cond, msg) static_assert(cond, msg)

MY_ASSERT(sizeof(void*) == 8, "64-bit system required");

void staticAssertDemo() {
    cout << "\n=== static_assert ===" << endl;

    // These pass at compile time
    Container<int> c1;      // OK
    Container<double> c2;   // OK

    // Container<std::string> c3;  // Would fail: not default constructible
    // Container<LargeStruct> c4;  // Would fail: too large

    cout << "All static_asserts passed at compile time!" << endl;
}

// ============================================
// MAIN() PROTOTYPES
// ============================================

// No arguments
int main_no_args() {
    return 0;
}

// With command-line arguments
int main_with_args(int argc, char* argv[]) {
    cout << "argc = " << argc << endl;
    for (int i = 0; i < argc; ++i) {
        cout << "argv[" << i << "] = " << argv[i] << endl;
    }
    return 0;
}

// ============================================
// COMMAND-LINE ARGUMENTS
// ============================================

void commandLineDemo(int argc, char* argv[]) {
    cout << "\n=== Command-Line Arguments ===" << endl;

    cout << "Program name: " << argv[0] << endl;
    cout << "Argument count: " << argc - 1 << endl;

    for (int i = 1; i < argc; ++i) {
        cout << "Arg " << i << ": " << argv[i] << endl;
    }

    // Parse options
    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            cout << "Help requested" << endl;
        } else if (arg == "-v" || arg == "--verbose") {
            cout << "Verbose mode" << endl;
        } else if (arg.rfind("-o=", 0) == 0) {
            cout << "Output file: " << arg.substr(3) << endl;
        }
    }
}

// ============================================
// PREPROCESSOR MACROS
// ============================================

#define SQUARE(x) ((x) * (x))  // Parentheses important!
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define STRINGIFY(x) #x
#define CONCAT(a, b) a##b

// Conditional compilation
#define DEBUG 1
#define VERSION "1.0.0"

void preprocessorDemo() {
    cout << "\n=== Preprocessor ===" << endl;

    int x = 5;
    cout << "SQUARE(5) = " << SQUARE(5) << endl;        // 25
    cout << "SQUARE(5+2) = " << SQUARE(5+2) << endl;    // 49 (with parens)
    cout << "MAX(10, 20) = " << MAX(10, 20) << endl;    // 20
    cout << "STRINGIFY(hello) = " << STRINGIFY(hello) << endl;  // "hello"
    cout << "CONCAT(var, 1) = " << CONCAT(var, 1) << endl;

    int var1 = 42;
    cout << "var1 = " << var1 << endl;

#if DEBUG
    cout << "Debug mode enabled" << endl;
#endif

    cout << "VERSION = " << VERSION << endl;

    // Predefined macros
    cout << "__FILE__ = " << __FILE__ << endl;
    cout << "__LINE__ = " << __LINE__ << endl;
    cout << "__DATE__ = " << __DATE__ << endl;
    cout << "__TIME__ = " << __TIME__ << endl;
    cout << "__cplusplus = " << __cplusplus << endl;
}

// ============================================
// COMPILATION STAGES DEMO
// ============================================

/*
Compilation Process:
1. Preprocessing:
   - #include expansion
   - #define replacement
   - #if/#ifdef conditional compilation
   - Output: translation unit (.i or .ii)

2. Compilation:
   - Translation unit -> assembly (.s)
   - Syntax checking, optimization
   - Output: object file (.o or .obj)

3. Linking:
   - Object files + libraries -> executable
   - Resolves external symbols
   - Output: executable
*/

// Header file simulation (would be in .h)
#define HEADER_GUARD_DEMO_H
#ifndef HEADER_GUARD_DEMO_H
#define HEADER_GUARD_DEMO_H

inline int headerFunc() { return 42; }

#endif

// Source file
int sourceFunc() { return headerFunc(); }

// ============================================
// COMPILER-SPECIFIC
// ============================================

// MSVC: #pragma warning(disable: 4996)
// GCC: #pragma GCC diagnostic ignored "-Wdeprecated"

// Platform detection
#if defined(_WIN32) || defined(_WIN64)
    #define PLATFORM_WINDOWS 1
#elif defined(__linux__)
    #define PLATFORM_LINUX 1
#elif defined(__APPLE__)
    #define PLATFORM_MACOS 1
#endif

// Compiler detection
#if defined(_MSC_VER)
    #define COMPILER_MSVC 1
    #define COMPILER_VERSION _MSC_VER
#elif defined(__GNUC__)
    #define COMPILER_GCC 1
    #define COMPILER_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#elif defined(__clang__)
    #define COMPILER_CLANG 1
    #define COMPILER_VERSION (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#endif

void compilerDemo() {
    cout << "\n=== Compiler/Platform Detection ===" << endl;

#if PLATFORM_WINDOWS
    cout << "Platform: Windows" << endl;
#elif PLATFORM_LINUX
    cout << "Platform: Linux" << endl;
#elif PLATFORM_MACOS
    cout << "Platform: macOS" << endl;
#endif

#if COMPILER_MSVC
    cout << "Compiler: MSVC " << COMPILER_VERSION << endl;
#elif COMPILER_GCC
    cout << "Compiler: GCC " << COMPILER_VERSION << endl;
#elif COMPILER_CLANG
    cout << "Compiler: Clang " << COMPILER_VERSION << endl;
#endif

    // Standard version
#if __cplusplus >= 202002L
    cout << "C++20 or later" << endl;
#elif __cplusplus >= 201703L
    cout << "C++17" << endl;
#elif __cplusplus >= 201402L
    cout << "C++14" << endl;
#elif __cplusplus >= 201103L
    cout << "C++11" << endl;
#endif
}

// ============================================
// ATTRIBUTES (C++11)
// ============================================

[[noreturn]] void neverReturns() {
    throw runtime_error("This function never returns");
}

[[deprecated("Use newFunction() instead")]]
void oldFunction() {
    cout << "Old function called" << endl;
}

[[nodiscard]] int mustUseResult() {
    return 42;
}

void attributesDemo() {
    cout << "\n=== Attributes ===" << endl;

    oldFunction();  // Warning: deprecated

    // mustUseResult();  // Warning: nodiscard return value ignored
    int result = mustUseResult();  // OK
    cout << "Result: " << result << endl;
}

// ============================================
// ALIGNMENT
// ============================================

// alignas specifier
struct alignas(16) Aligned16 {
    int x, y;
};

struct alignas(64) CacheLineAligned {
    int data[16];  // Fits in cache line
};

void alignmentDemo() {
    cout << "\n=== Alignment ===" << endl;

    cout << "alignof(int): " << alignof(int) << endl;
    cout << "alignof(double): " << alignof(double) << endl;
    cout << "alignof(Aligned16): " << alignof(Aligned16) << endl;
    cout << "alignof(CacheLineAligned): " << alignof(CacheLineAligned) << endl;

    // alignof expression
    int arr[10];
    cout << "alignof(arr): " << alignof(arr) << endl;

    // alignas on variable
    alignas(32) int alignedVar = 42;
    cout << "alignof(alignedVar): " << alignof(alignedVar) << endl;
}

int main(int argc, char* argv[]) {
    constexprDemo();
    staticAssertDemo();
    commandLineDemo(argc, argv);
    preprocessorDemo();
    compilerDemo();
    attributesDemo();
    alignmentDemo();

    return 0;
}