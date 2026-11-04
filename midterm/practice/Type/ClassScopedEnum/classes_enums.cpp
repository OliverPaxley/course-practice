// Classes and Scoped Enumerations - Practice Code for Midterm
// Topics: Class keys, data member initialization, copy/move operations, static members, structs, unions, enumerations

#include <iostream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// ============================================
// CLASS KEYS: class, struct, union
// ============================================

class StrongEncapsulation {
private:        // private by default
    int secret = 42;
public:
    int getSecret() const { return secret; }
};

struct WeakEncapsulation {
    int publicData = 100;  // public by default
};

union SharedMemory {
    int i;
    float f;
    char c[4];
    // All members share same memory address
    // Only one holds valid value at a time
};

// ============================================
// DATA MEMBER INITIALIZATION
// ============================================

class InitializationDemo {
    // Method 1: Default member initializers (in declaration)
    int defaultInit = 10;
    const string name = "Default";
    vector<int> vec = {1, 2, 3};

    // Method 2: Member list initializers (in constructor)
    int listInit;
    const string constMember;
    int& refMember;

public:
    // Method 3: Constructor body (cannot initialize const/ref here)
    InitializationDemo(int li, const string& cm, int& rm)
        : listInit(li), constMember(cm), refMember(rm) {
        // Body can only assign to non-const, non-ref members
        defaultInit = 20;  // Override default
    }

    void print() const {
        cout << "defaultInit: " << defaultInit << endl;
        cout << "name: " << name << endl;
        cout << "listInit: " << listInit << endl;
        cout << "constMember: " << constMember << endl;
        cout << "refMember: " << refMember << endl;
    }
};

// Counter for tracking constructions
int constructionCount = 0;

class TrackedObject {
    int id;
public:
    TrackedObject() : id(++constructionCount) {
        cout << "Default constructor: " << id << endl;
    }
    TrackedObject(const TrackedObject& other) : id(++constructionCount) {
        cout << "Copy constructor: " << id << " from " << other.id << endl;
    }
    TrackedObject(TrackedObject&& other) noexcept : id(++constructionCount) {
        cout << "Move constructor: " << id << " from " << other.id << endl;
        other.id = 0;
    }
    TrackedObject& operator=(const TrackedObject& other) {
        if (this != &other) {
            id = ++constructionCount;
            cout << "Copy assignment: " << id << " from " << other.id << endl;
        }
        return *this;
    }
    TrackedObject& operator=(TrackedObject&& other) noexcept {
        if (this != &other) {
            id = ++constructionCount;
            cout << "Move assignment: " << id << " from " << other.id << endl;
            other.id = 0;
        }
        return *this;
    }
    ~TrackedObject() {
        cout << "Destructor: " << id << endl;
    }
    int getId() const { return id; }
};

// ============================================
// COPY AND MOVE OPERATIONS
// ============================================

class Array {
    int* data;
    size_t size;
    int dummy;  // For out-of-bounds access

public:
    Array(size_t n = 10) : size(n), data(new int[n]), dummy(0) {
        for (size_t i = 0; i < size; ++i) data[i] = static_cast<int>(i);
    }

    // Copy constructor
    Array(const Array& other) : size(other.size), data(new int[other.size]), dummy(0) {
        for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
        cout << "Deep copy constructor" << endl;
    }

    // Copy assignment
    Array& operator=(const Array& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            data = new int[size];
            dummy = 0;
            for (size_t i = 0; i < size; ++i) data[i] = other.data[i];
            cout << "Deep copy assignment" << endl;
        }
        return *this;
    }

    // Move constructor
    Array(Array&& other) noexcept : data(other.data), size(other.size), dummy(other.dummy) {
        other.data = nullptr;
        other.size = 0;
        other.dummy = 0;
        cout << "Move constructor" << endl;
    }

    // Move assignment
    Array& operator=(Array&& other) noexcept {
        if (this != &other) {
            delete[] data;
            data = other.data;
            size = other.size;
            dummy = other.dummy;
            other.data = nullptr;
            other.size = 0;
            other.dummy = 0;
            cout << "Move assignment" << endl;
        }
        return *this;
    }

    ~Array() {
        delete[] data;
    }

    int& operator[](size_t i) {
        return (i < size) ? data[i] : dummy;
    }

    size_t getSize() const { return size; }
    int* getData() const { return data; }
};

void testCopyMove() {
    cout << "=== Copy vs Move Semantics ===" << endl;

    cout << "\n--- Copy ---" << endl;
    Array a1(5);
    Array a2 = a1;           // Copy constructor
    Array a3(3);
    a3 = a1;                 // Copy assignment

    cout << "\n--- Move ---" << endl;
    Array a4(5);
    Array a5 = std::move(a4);  // Move constructor
    Array a6(3);
    a6 = std::move(a5);        // Move assignment

    cout << "\na4 after move: size=" << a4.getSize() << ", data=" << a4.getData() << endl;
    cout << "a5 after move: size=" << a5.getSize() << ", data=" << a5.getData() << endl;
}

// ============================================
// STATIC MEMBERS (Class Variables/Functions)
// ============================================

class Horse {
    static unsigned count;    // Declaration only
    string name;

public:
    Horse(const string& n) : name(n) { ++count; }
    ~Horse() { --count; }

    // Static member function (class function)
    static unsigned howMany() { return count; }

    // Instance member function
    const string& getName() const { return name; }
};

// Definition required in implementation file
unsigned Horse::count = 0;

void testStaticMembers() {
    cout << "\n=== Static Members ===" << endl;
    cout << "Initial count: " << Horse::howMany() << endl;

    Horse h1("Secretariat");
    Horse h2("Seabiscuit");

    cout << "After 2 horses: " << Horse::howMany() << endl;
    cout << "h1 count: " << h1.howMany() << endl;  // Access via object
    cout << "Horse count: " << Horse::howMany() << endl;  // Access via class

    {
        Horse h3("Phar Lap");
        cout << "In block: " << Horse::howMany() << endl;
    }

    cout << "After block: " << Horse::howMany() << endl;
}

// ============================================
// STRUCTS AND UNIONS
// ============================================

struct Point {
    int x, y;  // Members arranged sequentially
    // May have padding between members for alignment
};

union Data {
    int i;
    float f;
    double d;
    char str[20];
    // All members share same address
    // Size = max member size (20 bytes for str)
};

struct DiscriminatedUnion {
    enum Type { INT, FLOAT, STRING } type;
    union {
        int i;
        float f;
        char str[20];
    } data;

    DiscriminatedUnion(int val) : type(INT) { data.i = val; }
    DiscriminatedUnion(float val) : type(FLOAT) { data.f = val; }
    DiscriminatedUnion(const char* val) : type(STRING) {
        strncpy(data.str, val, 19);
        data.str[19] = '\0';
    }

    void print() const {
        switch (type) {
            case INT: cout << "INT: " << data.i; break;
            case FLOAT: cout << "FLOAT: " << data.f; break;
            case STRING: cout << "STRING: " << data.str; break;
        }
        cout << endl;
    }
};

void testStructUnion() {
    cout << "\n=== Struct vs Union ===" << endl;

    Point p = {10, 20};
    cout << "Point size: " << sizeof(p) << endl;  // May be > 8 due to padding
    cout << "Point: (" << p.x << ", " << p.y << ")" << endl;

    Data d;
    d.i = 42;
    cout << "Data as int: " << d.i << endl;
    d.f = 3.14f;
    cout << "Data as float: " << d.f << endl;
    cout << "Data size: " << sizeof(d) << endl;  // 20 bytes

    DiscriminatedUnion du1(100);
    DiscriminatedUnion du2(3.14f);
    DiscriminatedUnion du3("Hello");
    du1.print();
    du2.print();
    du3.print();
}

// ============================================
// ENUMERATIONS
// ============================================

// Plain enumeration (unscoped)
enum Color { RED, GREEN, BLUE };
// Usage: Color c = RED;  // Unscoped access

// Scoped enumeration (enum class)
enum class ColorClass { RED, GREEN, BLUE };
// Usage: ColorClass c = ColorClass::RED;  // Scoped access required

// Scoped with custom underlying type and values
enum class Status : uint8_t {
    OK = 0x01,
    WARNING = 0x02,
    ERROR = 0x04,
    CRITICAL = 0x08
};

// Scoped with non-sequential values
enum class Priority { LOW = 10, MEDIUM = 20, HIGH = 30, CRITICAL = 40 };

void testEnumerations() {
    cout << "\n=== Enumerations ===" << endl;

    // Plain enum
    Color c1 = RED;
    Color c2 = GREEN;
    int val = RED;  // Implicit conversion to int
    cout << "Plain enum: RED=" << RED << ", GREEN=" << GREEN << ", BLUE=" << BLUE << endl;
    cout << "Implicit conversion: " << val << endl;

    // Scoped enum
    ColorClass cc1 = ColorClass::RED;
    ColorClass cc2 = ColorClass::GREEN;
    // int val2 = ColorClass::RED;  // ERROR: no implicit conversion
    int val2 = static_cast<int>(ColorClass::RED);  // Explicit cast required
    cout << "Scoped enum: RED=" << val2 << endl;
    cout << "Scoped enum prevents name collisions!" << endl;

    // Custom underlying type
    Status s = Status::OK;
    cout << "Status underlying type size: " << sizeof(Status) << endl;
    cout << "Status::OK = " << static_cast<uint8_t>(s) << endl;

    // Non-sequential values
    Priority p = Priority::HIGH;
    cout << "Priority::HIGH = " << static_cast<int>(p) << endl;

    // Switch with scoped enum
    switch (p) {
        case Priority::LOW: cout << "Low priority"; break;
        case Priority::MEDIUM: cout << "Medium priority"; break;
        case Priority::HIGH: cout << "High priority"; break;
        case Priority::CRITICAL: cout << "Critical priority"; break;
    }
    cout << endl;
}

// ============================================
// FORWARD DECLARATION AND ANONYMOUS CLASSES
// ============================================

class ForwardDeclared;  // Forward declaration

class UsesForward {
    ForwardDeclared* ptr;  // Can declare pointer/reference
    // ForwardDeclared obj;  // ERROR: incomplete type
};

class ForwardDeclared {
    int value;
public:
    ForwardDeclared(int v) : value(v) {}
    int getValue() const { return value; }
};

// Anonymous class (for type synonyms)
typedef struct {
    int x, y;
} AnonymousPoint;

void testForwardAnon() {
    cout << "\n=== Forward Declaration & Anonymous ===" << endl;

    ForwardDeclared fd(42);
    UsesForward uf;
    uf.ptr = &fd;
    cout << "Forward declared value: " << uf.ptr->getValue() << endl;

    AnonymousPoint ap = {1, 2};
    cout << "Anonymous point: (" << ap.x << ", " << ap.y << ")" << endl;
}

// ============================================
// SUB-OBJECT RESTRICTIONS
// ============================================

class Subject {
    Subject* prerequisite;  // OK: pointer to own type
    // Subject subj;         // ERROR: object of own type (infinite size)

public:
    Subject(Subject* pre = nullptr) : prerequisite(pre) {}
};

int main() {
    // Class keys
    StrongEncapsulation se;
    cout << "Strong encapsulation secret: " << se.getSecret() << endl;

    WeakEncapsulation we;
    cout << "Weak encapsulation public: " << we.publicData << endl;

    SharedMemory sm;
    sm.i = 0x41424344;
    cout << "Union as chars: " << sm.c[0] << sm.c[1] << sm.c[2] << sm.c[3] << endl;

    // Initialization
    int refVal = 100;
    InitializationDemo id(5, "ListInit", refVal);
    id.print();

    // Copy/Move
    testCopyMove();

    // Static members
    testStaticMembers();

    // Struct/Union
    testStructUnion();

    // Enumerations
    testEnumerations();

    // Forward/Anonymous
    testForwardAnon();

    return 0;
}