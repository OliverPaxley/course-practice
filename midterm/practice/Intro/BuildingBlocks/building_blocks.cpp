// C++ Building Blocks - Practice Code for Midterm
// Topics: Entities, declarations, definitions, ODR, scope, linkage, cv-qualifiers,
// storage duration, namespaces, variables vs objects, typedef

#include <iostream>
#include <string>

using namespace std;

// ============================================
// ENTITIES, DECLARATIONS, DEFINITIONS
// ============================================

// Declaration - introduces name
extern int externalVar;      // Declaration (no storage)
void externalFunc();         // Declaration

// Definition - associates meaning with name
int externalVar = 42;        // Definition (storage allocated)
void externalFunc() {        // Definition
    cout << "External function" << endl;
}

// One Definition Rule (ODR)
// A definition may not appear more than once across all translation units
// Multiple declarations OK, only one definition

// ============================================
// SCOPE
// ============================================

namespace NS {
    int nsVar = 100;  // Namespace scope
}

int globalVar = 10;  // Global scope

void scopeDemo() {
    cout << "=== Scope Demo ===" << endl;

    // Block scope
    {
        int blockVar = 20;  // Local/block scope
        cout << "blockVar: " << blockVar << endl;
    }
    // blockVar out of scope

    // C++17: init-statement scope extends to end of if/else
    if (int initVar = 5; initVar > 0) {
        cout << "initVar in if: " << initVar << endl;
    } else {
        cout << "initVar in else: " << initVar << endl;
    }
    // initVar out of scope

    // Global scope
    cout << "globalVar: " << globalVar << endl;
    cout << "::globalVar: " << ::globalVar << endl;  // Explicit global

    // Namespace scope
    cout << "NS::nsVar: " << NS::nsVar << endl;

    // Shadowing
    int globalVar = 30;  // Shadows global
    cout << "local globalVar: " << globalVar << endl;
    cout << "global ::globalVar: " << ::globalVar << endl;
}

// ============================================
// LINKAGE
// ============================================

// External linkage (default for non-static globals)
int externalLinkage = 1;
// In another file: extern int externalLinkage;

// Internal linkage - static at global scope
static int internalLinkage = 2;
// In another file: this is a DIFFERENT variable

// No linkage - local variables, class members
void linkageDemo() {
    int noLinkage = 3;  // No linkage

    cout << "externalLinkage: " << externalLinkage << " at " << &externalLinkage << endl;
    cout << "internalLinkage: " << internalLinkage << " at " << &internalLinkage << endl;
    cout << "noLinkage: " << noLinkage << " at " << &noLinkage << endl;
}

// ============================================
// CV-QUALIFIERS
// ============================================

void cvQualifiersDemo() {
    cout << "\n=== CV-Qualifiers ===" << endl;

    int mutableVar = 10;
    const int constVar = 20;           // Unmodifiable
    volatile int volatileVar = 30;     // Subject to side-effects
    const volatile int cvVar = 40;     // Both

    mutableVar = 100;  // OK
    // constVar = 200;   // ERROR: read-only

    // Pointer cv-qualifiers
    int value = 5;
    const int* ptrToConst = &value;    // Pointer to const int
    int* const constPtr = &value;      // Const pointer to int
    const int* const constPtrToConst = &value; // Const pointer to const int

    *ptrToConst = 10;  // ERROR: cannot modify through pointer to const
    // constPtr = &value;  // ERROR: const pointer cannot be reassigned

    // const_cast (remove const - dangerous!)
    // int* nonConst = const_cast<int*>(ptrToConst);
}

// ============================================
// STORAGE DURATION
// ============================================

// Static storage duration - program lifetime
static int staticDuration = 100;

void storageDurationDemo() {
    cout << "\n=== Storage Duration ===" << endl;

    // Automatic storage duration - block lifetime
    int autoVar = 10;

    // Static storage duration - program lifetime
    static int staticLocal = 0;
    staticLocal++;
    cout << "staticLocal: " << staticLocal << " (persists across calls)" << endl;

    // Dynamic storage duration - new/delete
    int* dynamicVar = new int(42);
    cout << "*dynamicVar: " << *dynamicVar << endl;
    delete dynamicVar;

    // Thread storage duration - thread lifetime
    thread_local int threadLocal = 0;
    threadLocal++;
    cout << "threadLocal: " << threadLocal << endl;
}

// ============================================
// NAMESPACES
// ============================================

namespace Math {
    const double PI = 3.14159;

    double square(double x) { return x * x; }
    double cube(double x) { return x * x * x; }
}

namespace Physics {
    const double G = 9.81;

    double force(double m, double a) { return m * a; }
}

// Anonymous namespace - internal linkage
namespace {
    int internalCounter = 0;
    void internalFunc() { cout << "Internal function" << endl; }
}

void namespaceDemo() {
    cout << "\n=== Namespaces ===" << endl;

    // Qualified access
    cout << "Math::PI: " << Math::PI << endl;
    cout << "Math::square(5): " << Math::square(5) << endl;

    // Using declaration - brings specific name
    using Math::cube;
    cout << "cube(3): " << cube(3) << endl;

    // Using directive - brings all names (avoid in headers!)
    using namespace Physics;
    cout << "force(10, 2): " << force(10, 2) << endl;
    cout << "G: " << G << endl;

    // Namespace alias
    namespace M = Math;
    cout << "M::PI: " << M::PI << endl;

    // Anonymous namespace
    internalCounter++;
    cout << "internalCounter: " << internalCounter << endl;
    internalFunc();
}

// ============================================
// VARIABLES VS OBJECTS
// ============================================

class MyClass {
public:
    MyClass() { cout << "MyClass constructed" << endl; }
    ~MyClass() { cout << "MyClass destroyed" << endl; }
};

void variablesVsObjects() {
    cout << "\n=== Variables vs Objects ===" << endl;

    MyClass* ptr;           // Variable (pointer), no object yet
    MyClass obj;            // Object AND variable (on stack)
    ptr = new MyClass();    // Object (on heap), not a variable
    MyClass& ref = obj;     // Reference to object

    cout << "ptr is variable, *ptr is object" << endl;
    cout << "obj is both variable and object" << endl;
    cout << "*ptr is object, not a variable" << endl;
    cout << "ref is reference to object" << endl;

    delete ptr;
}

// Subobject example
struct Base { int b; };
struct Derived : Base { int d; };

void subobjectDemo() {
    cout << "\n=== Subobjects ===" << endl;

    Derived derived;
    // derived has Base subobject and int d subobject
    // Base is a base class subobject of Derived
    // int d is a member subobject

    Base* basePtr = &derived;  // Base subobject address
    cout << "Derived address: " << &derived << endl;
    cout << "Base subobject address: " << basePtr << endl;
}

// ============================================
// TYPEDEF
// ============================================

typedef int Integer;
typedef const int ConstInt;
typedef int* IntPtr;
typedef int (*FuncPtr)(int, int);

void typedefDemo() {
    cout << "\n=== Typedef ===" << endl;

    Integer i = 42;
    ConstInt ci = 100;
    // ci = 200;  // ERROR: const

    int value = 10;
    IntPtr ptr = &value;
    cout << "*ptr = " << *ptr << endl;

    // Function pointer typedef
    FuncPtr fp = [](int a, int b) { return a + b; };
    cout << "fp(3, 4) = " << fp(3, 4) << endl;

    // Using alias (C++11, preferred)
    using IntegerAlias = int;
    using FuncAlias = int(*)(int, int);

    IntegerAlias ia = 5;
    FuncAlias fa = [](int a, int b) { return a * b; };
    cout << "fa(3, 4) = " << fa(3, 4) << endl;
}

// ============================================
// FORWARD DECLARATION
// ============================================

class ForwardDeclared;  // Forward declaration

class UsesForward {
    ForwardDeclared* ptr;  // OK: pointer to incomplete type
    // ForwardDeclared obj;  // ERROR: incomplete type
};

class ForwardDeclared {
    int value;
public:
    ForwardDeclared(int v) : value(v) {}
    int getValue() const { return value; }
};

void forwardDeclDemo() {
    cout << "\n=== Forward Declaration ===" << endl;

    ForwardDeclared fd(42);
    UsesForward uf;
    uf.ptr = &fd;
    cout << "Forward declared value: " << uf.ptr->getValue() << endl;
}

// ============================================
// ANONYMOUS CLASS/STRUCT
// ============================================

typedef struct {
    int x, y;
} Point;

void anonymousStructDemo() {
    cout << "\n=== Anonymous Struct ===" << endl;

    Point p = {10, 20};
    cout << "Point: (" << p.x << ", " << p.y << ")" << endl;
}

int main() {
    scopeDemo();
    linkageDemo();
    cvQualifiersDemo();
    storageDurationDemo();
    namespaceDemo();
    variablesVsObjects();
    subobjectDemo();
    typedefDemo();
    forwardDeclDemo();
    anonymousStructDemo();

    return 0;
}