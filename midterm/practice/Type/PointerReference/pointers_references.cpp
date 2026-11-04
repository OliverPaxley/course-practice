// Pointers, References, and Arrays - Practice Code for Midterm
// Topics: Pointer types, null pointers, generic pointers, references (lvalue/rvalue), arrays, aggregate initialization, range-based for

#include <iostream>
#include <iomanip>
#include <utility>
#include <memory>

using namespace std;

void pointerBasics() {
    cout << "=== Pointer Basics ===" << endl;

    int x = 10;
    int* p = &x;           // Pointer to int
    int** pp = &p;         // Pointer to pointer

    cout << "x = " << x << endl;
    cout << "&x = " << &x << endl;
    cout << "p = " << p << endl;
    cout << "*p = " << *p << endl;
    cout << "pp = " << pp << endl;
    cout << "*pp = " << *pp << endl;
    cout << "**pp = " << **pp << endl;
}

void nullptrUsage() {
    cout << "\n=== nullptr Usage ===" << endl;

    int* p1 = nullptr;         // Initialize to nullptr
    int* p2 = 0;               // Old style (works but not recommended)
    int* p3 = NULL;            // C-style macro (not recommended in C++)

    if (!p1) {
        cout << "p1 is null" << endl;
    }

    // Dereferencing nullptr causes runtime error
    // int* bad = nullptr;
    // *bad = 5;  // CRASH!

    // Good practice: check before dereferencing
    int* ptr = nullptr;
    if (ptr != nullptr) {
        *ptr = 10;
    } else {
        cout << "Pointer is null, safe!" << endl;
    }
}

void pointerArithmetic() {
    cout << "\n=== Pointer Arithmetic ===" << endl;

    int arr[5] = {10, 20, 30, 40, 50};
    int* p = arr;              // Points to arr[0]

    cout << "*p = " << *p << endl;        // 10
    cout << "*(p+1) = " << *(p+1) << endl; // 20
    cout << "p[2] = " << p[2] << endl;     // 30

    p += 2;                    // Points to arr[2]
    cout << "*p = " << *p << endl;        // 30

    int* q = p - 1;            // Points to arr[1]
    cout << "*q = " << *q << endl;        // 20

    ptrdiff_t diff = p - q;    // Difference in elements
    cout << "p - q = " << diff << endl;   // 1

    // Negative subscripts
    int* mid = &arr[2];
    cout << "mid[-1] = " << mid[-1] << endl;  // 20
    cout << "mid[-2] = " << mid[-2] << endl;  // 10
}

void voidPointers() {
    cout << "\n=== Void Pointers (Generic Pointers) ===" << endl;

    int i = 42;
    double d = 3.14;

    void* vp = &i;             // Can hold any pointer type
    vp = &d;                   // Can be reassigned

    // Must cast back to dereference
    cout << "*static_cast<int*>(vp) = " << *static_cast<int*>(vp) << endl; // WRONG! vp points to double

    vp = &i;
    cout << "*static_cast<int*>(vp) = " << *static_cast<int*>(vp) << endl; // Correct

    // Hex dump example
    auto hexDump = [](void* addr, size_t n) {
        unsigned char* bytes = static_cast<unsigned char*>(addr);
        for (size_t i = 0; i < n; ++i) {
            cout << hex << setw(2) << setfill('0') << static_cast<int>(bytes[i]) << ' ';
        }
        cout << dec << endl;
    };

    int val = 0x01020304;
    cout << "Hex dump of int (little-endian): ";
    hexDump(&val, sizeof(val));
}

void synonymPointers() {
    cout << "\n=== Synonym Pointer Types (typedef) ===" << endl;

    typedef int* IntPtr;
    typedef const int* ConstIntPtr;

    int a = 10, b = 20;
    IntPtr p1 = &a, p2 = &b;   // No * needed before each identifier
    ConstIntPtr cp = &a;       // Pointer to const int

    cout << "*p1 = " << *p1 << ", *p2 = " << *p2 << endl;
    cout << "*cp = " << *cp << endl;

    // Compare with direct syntax
    int* dp1, *dp2;            // Must put * before each
}

void lvalueReferences() {
    cout << "\n=== Lvalue References ===" << endl;

    int x = 10;
    int& ref = x;              // Must initialize (unless extern, class member, or parameter)
    ref = 20;                  // Modifies x

    cout << "x = " << x << endl;        // 20
    cout << "ref = " << ref << endl;    // 20

    // Reference to const (can bind to rvalue)
    const int& cref = 30;      // Binds to temporary
    // int& badRef = 30;       // ERROR: non-const lvalue ref cannot bind to rvalue

    // Reference restrictions
    // int& ref2;              // ERROR: must initialize
    // int& ref3 = ref;        // OK: ref to ref (but ref3 refers to x)
    // int& arr[3];            // ERROR: no arrays of references
    // int*& ptrRef = ref;     // ERROR: no pointers to references
}

void rvalueReferences() {
    cout << "\n=== Rvalue References ===" << endl;

    int x = 10;
    int&& rref = 20;           // Binds to rvalue (temporary)
    int&& rref2 = std::move(x); // Cast lvalue to rvalue reference

    cout << "rref = " << rref << endl;
    cout << "rref2 = " << rref2 << endl;

    // Overload resolution - use function objects for overloading
    struct PrintOverload {
        void operator()(const int& lval) { cout << "lvalue: " << lval << endl; }
        void operator()(int&& rval) { cout << "rvalue: " << rval << endl; }
    };

    PrintOverload print;
    int a = 10;
    print(a);           // Calls lvalue version
    print(20);          // Calls rvalue version
    print(std::move(a)); // Calls rvalue version
}

void stdRefAndMove() {
    cout << "\n=== std::ref and std::move ===" << endl;

    int x = 10;
    auto lref = std::ref(x);        // std::reference_wrapper<int>
    auto rref = std::move(x);       // int&&

    cout << "lref.get() = " << lref.get() << endl;
    cout << "rref = " << rref << endl;

    // Use case: passing by reference to algorithms
    auto modify = [](int& val) { val *= 2; };
    modify(lref);                   // Modifies x
    cout << "After modify: x = " << x << endl;
}

void arrayBasics() {
    cout << "\n=== Array Basics ===" << endl;

    // Stack allocation
    int stackArr[5] = {1, 2, 3, 4, 5};
    int stackArr2[] = {10, 20, 30};  // Size deduced

    // Heap allocation
    int* heapArr = new int[5]{1, 2, 3, 4, 5};
    int* heapArr2 = new int[5]{};    // Value-initialized to zeros

    cout << "Stack array: ";
    for (int i = 0; i < 5; ++i) cout << stackArr[i] << ' ';
    cout << endl;

    cout << "Heap array: ";
    for (int i = 0; i < 5; ++i) cout << heapArr[i] << ' ';
    cout << endl;

    delete[] heapArr;
    delete[] heapArr2;
}

void aggregateInitialization() {
    cout << "\n=== Aggregate Initialization ===" << endl;

    // Different syntaxes
    int a1[5] = {1, 2, 3};        // Remaining elements = 0
    int a2[5] {4, 5, 6};          // Remaining elements = 0
    int a3[] = {7, 8, 9};         // Size = 3
    int a4[] {10, 11};            // Size = 2
    int a5[5] {};                 // All zeros
    int a6[5] = {};               // All zeros

    cout << "a1: "; for (int x : a1) cout << x << ' '; cout << endl;
    cout << "a2: "; for (int x : a2) cout << x << ' '; cout << endl;
    cout << "a3: "; for (int x : a3) cout << x << ' '; cout << endl;
    cout << "a4: "; for (int x : a4) cout << x << ' '; cout << endl;
    cout << "a5: "; for (int x : a5) cout << x << ' '; cout << endl;
    cout << "a6: "; for (int x : a6) cout << x << ' '; cout << endl;

    // Heap with aggregate init
    int* h1 = new int[5]{1, 2};
    int* h2 = new int[5]{};

    cout << "h1: "; for (int i = 0; i < 5; ++i) cout << h1[i] << ' '; cout << endl;
    cout << "h2: "; for (int i = 0; i < 5; ++i) cout << h2[i] << ' '; cout << endl;

    delete[] h1;
    delete[] h2;
}

void rangeBasedFor() {
    cout << "\n=== Range-Based For ===" << endl;

    int arr[]{1, 2, 3, 4, 5, 6};

    // By reference - can modify
    cout << "Modify: ";
    for (int& e : arr) {
        e *= 2;
        cout << e << ' ';
    }
    cout << endl;

    // By value - read only
    cout << "Read: ";
    for (auto e : arr) {          // auto deduces int
        cout << e << ' ';
    }
    cout << endl;

    // By const reference - read only, no copy
    cout << "Const ref: ";
    for (const auto& e : arr) {
        cout << e << ' ';
    }
    cout << endl;

    // Works with stack arrays, NOT raw pointers
    int* ptr = new int[3]{10, 20, 30};
    // for (int e : ptr) { }      // ERROR: no bounds known

    // But works with std::array, std::vector, etc.
    delete[] ptr;
}

void arrayDecay() {
    cout << "\n=== Array Decay ===" << endl;

    int arr[5] = {1, 2, 3, 4, 5};

    // Array name decays to pointer in most contexts
    int* ptr = arr;               // Decays to int*
    cout << "sizeof(arr) = " << sizeof(arr) << endl;     // 20 bytes (5 * 4)
    cout << "sizeof(ptr) = " << sizeof(ptr) << endl;     // 8 bytes (pointer size)

    // Exception: sizeof and & operators
    cout << "&arr = " << &arr << " (type: int(*)[5])" << endl;
    cout << "&arr[0] = " << &arr[0] << " (type: int*)" << endl;

    // Function parameter - array decays
    auto printSize = [](int p[]) {
        cout << "In function, sizeof(p) = " << sizeof(p) << endl; // Pointer size
    };
    printSize(arr);
}

void multiDimArrays() {
    cout << "\n=== Multi-Dimensional Arrays ===" << endl;

    // Stack
    int matrix[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    cout << "matrix[1][2] = " << matrix[1][2] << endl;  // 7
    cout << "matrix[2][3] = " << matrix[2][3] << endl;  // 12

    // Range-based for with multi-dim
    cout << "All elements: ";
    for (auto& row : matrix) {
        for (int& elem : row) {
            cout << elem << ' ';
        }
    }
    cout << endl;

    // Pointer to array
    int (*p)[4] = matrix;         // Pointer to array of 4 ints
    cout << "(*p)[2] = " << (*p)[2] << endl;  // 3
    p++;
    cout << "(*p)[0] = " << (*p)[0] << endl;  // 5
}

int main() {
    pointerBasics();
    nullptrUsage();
    pointerArithmetic();
    voidPointers();
    synonymPointers();
    lvalueReferences();
    rvalueReferences();
    stdRefAndMove();
    arrayBasics();
    aggregateInitialization();
    rangeBasedFor();
    arrayDecay();
    multiDimArrays();

    return 0;
}