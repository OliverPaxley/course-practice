// Error Handling - Practice Code for Midterm
// Topics: Exceptions, try/catch, standard exception hierarchy, noexcept,
// standard exits, abnormal exits

#include <iostream>
#include <exception>
#include <stdexcept>
#include <new>
#include <typeinfo>
#include <vector>
#include <string>

using namespace std;

// ============================================
// BASIC EXCEPTION HANDLING
// ============================================

void divide(double a[], int i, int n, double divisor) {
    if (i < 0 || i >= n) throw "Outside bounds";      // const char*
    else if (divisor == 0) throw divisor;             // double
    else a[i] = i / divisor;
}

void basicExceptionDemo() {
    cout << "=== Basic Exception Handling ===" << endl;

    double arr[5] = {0};

    try {
        divide(arr, 2, 5, 2.0);   // OK
        cout << "arr[2] = " << arr[2] << endl;
    } catch (const char* msg) {
        cout << "Caught const char*: " << msg << endl;
    } catch (double d) {
        cout << "Caught double: " << d << endl;
    } catch (...) {
        cout << "Caught unknown exception" << endl;
    }

    try {
        divide(arr, 10, 5, 2.0);  // Out of bounds
    } catch (const char* msg) {
        cout << "Caught: " << msg << endl;
    }

    try {
        divide(arr, 2, 5, 0.0);   // Division by zero
    } catch (double d) {
        cout << "Caught divisor: " << d << endl;
    }
}

// ============================================
// STANDARD EXCEPTION HIERARCHY
// ============================================

void standardExceptionsDemo() {
    cout << "\n=== Standard Exception Hierarchy ===" << endl;

    // bad_alloc from new
    try {
        // Allocate huge array (may throw bad_alloc)
        // size_t huge = SIZE_MAX;
        // int* p = new int[huge];  // Commented out to avoid crash
        cout << "Allocation skipped (would throw bad_alloc)" << endl;
    } catch (const bad_alloc& e) {
        cout << "bad_alloc: " << e.what() << endl;
    }

    // logic_error derivatives
    try {
        throw out_of_range("Index out of range");
    } catch (const out_of_range& e) {
        cout << "out_of_range: " << e.what() << endl;
    } catch (const logic_error& e) {
        cout << "logic_error: " << e.what() << endl;
    }

    // runtime_error derivatives
    try {
        throw runtime_error("Runtime error occurred");
    } catch (const runtime_error& e) {
        cout << "runtime_error: " << e.what() << endl;
    }

    // Catch order matters! Most derived first
    try {
        throw invalid_argument("Invalid argument");
    } catch (const invalid_argument& e) {
        cout << "invalid_argument (derived): " << e.what() << endl;
    } catch (const logic_error& e) {
        cout << "logic_error (base): " << e.what() << endl;
    } catch (const exception& e) {
        cout << "exception (base of all): " << e.what() << endl;
    }

    // bad_cast from dynamic_cast
    struct Base { virtual ~Base() = default; };
    struct Derived : Base { int x = 42; };

    Base* b = new Base();
    try {
        Derived& d = dynamic_cast<Derived&>(*b);  // Throws bad_cast
    } catch (const bad_cast& e) {
        cout << "bad_cast: " << e.what() << endl;
    }
    delete b;
}

// ============================================
// CUSTOM EXCEPTION CLASSES
// ============================================

class MyException : public exception {
    string message;
public:
    MyException(const string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class NetworkException : public MyException {
    int errorCode;
public:
    NetworkException(const string& msg, int code) : MyException(msg), errorCode(code) {}
    int getCode() const { return errorCode; }
};

void customExceptionsDemo() {
    cout << "\n=== Custom Exception Classes ===" << endl;

    auto riskyOperation = [](bool fail) {
        if (fail) throw NetworkException("Connection timeout", 1001);
        cout << "Operation succeeded" << endl;
    };

    try {
        riskyOperation(true);
    } catch (const NetworkException& e) {
        cout << "NetworkException: " << e.what() << ", code: " << e.getCode() << endl;
    } catch (const MyException& e) {
        cout << "MyException: " << e.what() << endl;
    }

    // Rethrowing
    try {
        try {
            throw MyException("Inner exception");
        } catch (const MyException& e) {
            cout << "Caught: " << e.what() << endl;
            throw;  // Rethrow same exception
        }
    } catch (const MyException& e) {
        cout << "Rethrown: " << e.what() << endl;
    }
}

// ============================================
// NOEXCEPT
// ============================================

void mayThrow() {
    throw runtime_error("This throws");
}

void noThrow() noexcept {
    cout << "This function promises not to throw" << endl;
}

void callsNoThrow() noexcept {
    noThrow();  // OK - noThrow is noexcept
}

void callsMayThrow() noexcept {
    // mayThrow();  // If uncommented: TERMINATES if mayThrow throws!
}

void noexceptDemo() {
    cout << "\n=== noexcept ===" << endl;

    // noexcept operator (compile-time check)
    cout << "noexcept(noThrow()): " << noexcept(noThrow()) << endl;
    cout << "noexcept(mayThrow()): " << noexcept(mayThrow()) << endl;
    cout << "noexcept(1 + 2): " << noexcept(1 + 2) << endl;

    // noexcept functions can call noexcept functions
    callsNoThrow();

    // Violation at runtime = immediate termination
    // Uncomment to test termination:
    // callsMayThrow();

    // Conditional noexcept
    template <typename T>
    void process(T& obj) noexcept(noexcept(obj.process())) {
        obj.process();
    }

    struct Safe {
        void process() noexcept { cout << "Safe::process()" << endl; }
    };

    struct Unsafe {
        void process() { cout << "Unsafe::process()" << endl; }
    };

    Safe s;
    process(s);  // noexcept(process(s)) = true

    // Unsafe u;
    // process(u);  // noexcept(process(u)) = false
}

// ============================================
// EXCEPTION SAFETY GUARANTEES
// ============================================

class ExceptionSafe {
    vector<int> data;
public:
    // Strong guarantee: either succeeds or state unchanged
    void push_back_strong(int value) {
        data.push_back(value);  // vector::push_back has strong guarantee
    }

    // Basic guarantee: no leaks, valid state but possibly modified
    void push_back_basic(int value) {
        data.insert(data.begin(), value);  // May throw after moving elements
    }

    // Nothrow guarantee: never throws
    size_t size() const noexcept { return data.size(); }
};

void exceptionSafetyDemo() {
    cout << "\n=== Exception Safety ===" << endl;

    ExceptionSafe safe;
    safe.push_back_strong(1);
    safe.push_back_strong(2);
    cout << "Size: " << safe.size() << endl;

    // Copy-and-swap idiom for strong guarantee
    class Resource {
        int* data;
        size_t size;
    public:
        Resource(size_t n) : size(n), data(new int[n]) {}
        ~Resource() { delete[] data; }

        // Copy constructor
        Resource(const Resource& other) : size(other.size), data(new int[other.size]) {
            copy(other.data, other.data + size, data);
        }

        // Copy assignment using copy-and-swap
        Resource& operator=(Resource other) {  // Pass by value (copy)
            swap(data, other.data);
            swap(size, other.size);
            return *this;
        }

        // Move constructor
        Resource(Resource&& other) noexcept : data(other.data), size(other.size) {
            other.data = nullptr;
            other.size = 0;
        }
    };
}

// ============================================
// UNCAUGHT EXCEPTIONS
// ============================================

void uncaughtExceptionsDemo() {
    cout << "\n=== Uncaught Exceptions ===" << endl;

    // std::uncaught_exceptions() returns count during stack unwinding
    struct Checker {
        ~Checker() {
            cout << "Destructor: uncaught_exceptions = "
                 << uncaught_exceptions() << endl;
        }
    };

    try {
        Checker c;
        throw runtime_error("Test");
    } catch (...) {
        cout << "Caught in handler" << endl;
    }

    // If no handler: std::terminate() called
}

// ============================================
// STANDARD EXITS
// ============================================

// Normal exit - executes destructors, atexit handlers
void normalExitDemo() {
    cout << "\n=== Normal Exit ===" << endl;

    // atexit registers cleanup functions (max 32)
    void cleanup1() { cout << "Cleanup 1" << endl; }
    void cleanup2() { cout << "Cleanup 2" << endl; }

    atexit(cleanup1);
    atexit(cleanup2);

    cout << "About to exit..." << endl;
    // exit(0);  // Would call cleanups in reverse order (cleanup2, cleanup1)
    // return 0;  // Also normal exit

    // For demo, manually call cleanups
    cleanup2();
    cleanup1();
}

// Abnormal exit - NO destructors, NO atexit handlers
void abnormalExitDemo() {
    cout << "\n=== Abnormal Exit ===" << endl;

    struct NoDestructor {
        ~NoDestructor() { cout << "Destructor called" << endl; }
    };

    // terminate - called when no handler, noexcept violation, etc.
    // std::terminate();  // Would not call destructor!

    // abort - immediate termination via SIGABRT
    // std::abort();  // No cleanup at all!

    cout << "Demonstrating without actually terminating..." << endl;
    NoDestructor obj;
    cout << "Object created, destructor would run on normal exit" << endl;
}

// ============================================
// EXPRESSIONS THAT THROW
// ============================================

void throwingExpressionsDemo() {
    cout << "\n=== Expressions That Throw ===" << endl;

    // 1. throw expression
    auto throwExpr = []() { throw 42; };

    // 2. dynamic_cast (reference)
    struct Base { virtual ~Base() = default; };
    struct Derived : Base { int x = 42; };

    Base* b = new Base();
    try {
        Derived& d = dynamic_cast<Derived&>(*b);  // Throws bad_cast
    } catch (const bad_cast&) {
        cout << "dynamic_cast reference throws bad_cast" << endl;
    }
    delete b;

    // 3. typeid on null pointer
    Derived* d = nullptr;
    try {
        typeid(*d);  // Throws bad_typeid
    } catch (const bad_typeid&) {
        cout << "typeid(null) throws bad_typeid" << endl;
    }

    // 4. new expression
    try {
        // size_t huge = SIZE_MAX;
        // int* p = new int[huge];  // Throws bad_alloc
        cout << "new expression throws bad_alloc on failure" << endl;
    } catch (const bad_alloc&) {
        cout << "Caught bad_alloc" << endl;
    }
}

// ============================================
// RAII AND EXCEPTIONS
// ============================================

class FileHandle {
    FILE* file;
public:
    FileHandle(const char* name, const char* mode) : file(fopen(name, mode)) {
        if (!file) throw runtime_error("Failed to open file");
        cout << "File opened: " << name << endl;
    }
    ~FileHandle() {
        if (file) {
            fclose(file);
            cout << "File closed" << endl;
        }
    }
    // Non-copyable
    FileHandle(const FileHandle&) = delete;
    FileHandle& operator=(const FileHandle&) = delete;
    // Movable
    FileHandle(FileHandle&& other) noexcept : file(other.file) {
        other.file = nullptr;
    }
    FileHandle& operator=(FileHandle&& other) noexcept {
        if (this != &other) {
            if (file) fclose(file);
            file = other.file;
            other.file = nullptr;
        }
        return *this;
    }
    FILE* get() const { return file; }
};

void raiiDemo() {
    cout << "\n=== RAII and Exceptions ===" << endl;

    try {
        FileHandle f("test.txt", "w");
        // If exception thrown here, destructor closes file
        throw runtime_error("Something went wrong");
    } catch (const exception& e) {
        cout << "Caught: " << e.what() << endl;
        // File automatically closed by destructor!
    }

    // Smart pointers also provide RAII
    auto ptr = make_unique<int>(42);
    // If exception thrown, unique_ptr deletes the int
}

int main() {
    basicExceptionDemo();
    standardExceptionsDemo();
    customExceptionsDemo();
    noexceptDemo();
    exceptionSafetyDemo();
    uncaughtExceptionsDemo();
    normalExitDemo();
    abnormalExitDemo();
    throwingExpressionsDemo();
    raiiDemo();

    return 0;
}