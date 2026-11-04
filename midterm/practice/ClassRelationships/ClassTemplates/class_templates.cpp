// Class Templates - Practice Code for Midterm
// Topics: Template syntax, parameters, function templates, class templates, specialization,
// non-type parameters, default parameters, static members, templates and inheritance, variadic templates

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <type_traits>

using namespace std;

// ============================================
// FUNCTION TEMPLATES
// ============================================

template <typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
T maximum(T a, T b) {
    return (a > b) ? a : b;
}

// Overloading vs Specialization
template <typename T>
T add(T a, T b) {
    return a + b;
}

// Specialization for const char*
template <>
const char* add<const char*>(const char* a, const char* b) {
    // This won't work well for string concatenation
    // Just return the longer one for demo
    return (strlen(a) > strlen(b)) ? a : b;
}

// Better: Overload instead of specialize
const char* add(const char* a, const char* b) {
    static string result = string(a) + b;
    return result.c_str();
}

void functionTemplatesDemo() {
    cout << "=== Function Templates ===" << endl;

    int a = 5, b = 10;
    swapValues(a, b);
    cout << "After swap: a=" << a << ", b=" << b << endl;

    cout << "Max(3, 7): " << maximum(3, 7) << endl;
    cout << "Max(3.14, 2.71): " << maximum(3.14, 2.71) << endl;
    cout << "Max('a', 'z'): " << maximum('a', 'z') << endl;

    // Explicit template argument
    cout << "Max<double>(3, 7.5): " << maximum<double>(3, 7.5) << endl;

    // Specialization vs Overloading
    cout << "Add(3, 4): " << add(3, 4) << endl;
    cout << "Add(3.5, 2.5): " << add(3.5, 2.5) << endl;
    cout << "Add(\"Hello\", \"World\"): " << add("Hello", "World") << endl;
}

// ============================================
// CLASS TEMPLATES
// ============================================

template <typename T, int SIZE = 10>
class FixedArray {
    T data[SIZE];
    size_t count;

public:
    FixedArray() : count(0) {}

    void push(const T& value) {
        if (count < SIZE) {
            data[count++] = value;
        }
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    size_t size() const { return count; }
    size_t capacity() const { return SIZE; }

    void print() const {
        cout << "[";
        for (size_t i = 0; i < count; ++i) {
            cout << data[i];
            if (i < count - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

template <typename T>
class DynamicArray {
    T* data;
    size_t capacity;
    size_t count;

public:
    DynamicArray(size_t cap = 10) : capacity(cap), count(0) {
        data = new T[capacity];
    }

    // Copy constructor
    DynamicArray(const DynamicArray& other)
        : capacity(other.capacity), count(other.count) {
        data = new T[capacity];
        for (size_t i = 0; i < count; ++i) data[i] = other.data[i];
    }

    // Move constructor
    DynamicArray(DynamicArray&& other) noexcept
        : data(other.data), capacity(other.capacity), count(other.count) {
        other.data = nullptr;
        other.capacity = 0;
        other.count = 0;
    }

    ~DynamicArray() { delete[] data; }

    void push(const T& value) {
        if (count >= capacity) {
            resize(capacity * 2);
        }
        data[count++] = value;
    }

    T& operator[](size_t index) { return data[index]; }
    size_t size() const { return count; }

    void print() const {
        cout << "[";
        for (size_t i = 0; i < count; ++i) {
            cout << data[i];
            if (i < count - 1) cout << ", ";
        }
        cout << "]" << endl;
    }

private:
    void resize(size_t newCap) {
        T* newData = new T[newCap];
        for (size_t i = 0; i < count; ++i) newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }
};

void classTemplatesDemo() {
    cout << "\n=== Class Templates ===" << endl;

    // FixedArray with default size
    FixedArray<int> intArray;
    intArray.push(1);
    intArray.push(2);
    intArray.push(3);
    cout << "FixedArray<int>: ";
    intArray.print();

    // FixedArray with explicit size
    FixedArray<double, 5> doubleArray;
    doubleArray.push(1.1);
    doubleArray.push(2.2);
    cout << "FixedArray<double, 5>: ";
    doubleArray.print();

    // DynamicArray
    DynamicArray<string> strArray;
    strArray.push("Hello");
    strArray.push("World");
    strArray.push("Templates");
    cout << "DynamicArray<string>: ";
    strArray.print();
}

// ============================================
// NON-TYPE TEMPLATE PARAMETERS
// ============================================

// Non-type parameters can be:
// - Integral types
// - Enum types
// - Pointers
// - Lvalue references
// - Pointer to member
// - std::nullptr_t
// - auto (C++17)

template <int SIZE>
class Stack {
    int data[SIZE];
    int top;
public:
    Stack() : top(-1) {}

    void push(int value) {
        if (top < SIZE - 1) data[++top] = value;
    }

    int pop() {
        return (top >= 0) ? data[top--] : -1;
    }

    bool empty() const { return top == -1; }
    int size() const { return top + 1; }
};

// Template template parameter
template <template <typename> class Container, typename T>
class ContainerWrapper {
    Container<T> container;
public:
    void add(const T& item) { container.push_back(item); }
    void print() const {
        for (const auto& item : container) cout << item << ' ';
        cout << endl;
    }
};

void nonTypeParamsDemo() {
    cout << "\n=== Non-Type Template Parameters ===" << endl;

    Stack<5> s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout << "Stack size: " << s.size() << endl;
    cout << "Pop: " << s.pop() << endl;
    cout << "Pop: " << s.pop() << endl;

    // Template template parameter
    ContainerWrapper<vector, int> wrapper;
    wrapper.add(10);
    wrapper.add(20);
    wrapper.add(30);
    wrapper.print();
}

// ============================================
// DEFAULT TEMPLATE PARAMETERS
// ============================================

template <typename T = int, int SIZE = 10>
class ConfigurableArray {
    T data[SIZE];
public:
    ConfigurableArray() { data[0] = T(); }
    T getFirst() const { return data[0]; }
};

void defaultParamsDemo() {
    cout << "\n=== Default Template Parameters ===" << endl;

    ConfigurableArray<> arr1;        // T=int, SIZE=10
    ConfigurableArray<double> arr2;  // T=double, SIZE=10
    ConfigurableArray<char, 20> arr3; // T=char, SIZE=20

    cout << "ConfigurableArray<>: " << arr1.getFirst() << endl;
    cout << "ConfigurableArray<double>: " << arr2.getFirst() << endl;
    cout << "ConfigurableArray<char, 20>: " << arr3.getFirst() << endl;
}

// ============================================
// STATIC DATA MEMBERS IN TEMPLATES
// ============================================

template <typename T>
class Counter {
    static int count;  // Each instantiation gets its own static member
public:
    Counter() { ++count; }
    ~Counter() { --count; }
    static int getCount() { return count; }
};

// Definition required for each template instantiation
// Template definition (one for all)
template <typename T>
int Counter<T>::count = 0;

void staticMembersDemo() {
    cout << "\n=== Static Members in Templates ===" << endl;

    Counter<int> ci1, ci2;
    Counter<double> cd1;

    cout << "Counter<int> count: " << Counter<int>::getCount() << endl;    // 2
    cout << "Counter<double> count: " << Counter<double>::getCount() << endl; // 1
    cout << "Counter<string> count: " << Counter<string>::getCount() << endl; // 0
}

// ============================================
// TEMPLATES AND INHERITANCE
// ============================================

template <typename T>
class BaseTemplate {
protected:
    T value;
public:
    BaseTemplate(T v) : value(v) {}
    virtual void print() const { cout << "Base: " << value << endl; }
};

template <typename T, typename U>
class DerivedTemplate : public BaseTemplate<T> {
    U extra;
public:
    DerivedTemplate(T v, U e) : BaseTemplate<T>(v), extra(e) {}
    void print() const override {
        cout << "Derived: " << this->value << ", " << extra << endl;
    }
};

// Derived can add its own template parameters
template <typename V>
class FurtherDerived : public BaseTemplate<int> {
    V more;
public:
    FurtherDerived(int v, V m) : BaseTemplate<int>(v), more(m) {}
    void print() const override {
        cout << "FurtherDerived: " << this->value << ", " << more << endl;
    }
};

void inheritanceDemo() {
    cout << "\n=== Templates and Inheritance ===" << endl;

    BaseTemplate<int> base(42);
    DerivedTemplate<int, double> derived(10, 3.14);
    FurtherDerived<string> further(5, "extra");

    base.print();
    derived.print();
    further.print();

    // Polymorphism with templates
    BaseTemplate<int>* ptr = &derived;
    ptr->print();  // Calls Derived::print()
}

// ============================================
// VARIADIC TEMPLATES
// ============================================

// Base case
void print() {
    cout << endl;
}

// Recursive variadic template
template <typename T, typename... Args>
void print(T first, Args... rest) {
    cout << first << ' ';
    print(rest...);
}

// Variadic template with fold expression (C++17)
template <typename... Args>
auto sum(Args... args) {
    return (args + ...);  // Fold expression
}

// Variadic template class
template <typename... Types>
class Tuple;

template <>
class Tuple<> {};  // Empty tuple

template <typename Head, typename... Tail>
class Tuple<Head, Tail...> : private Tuple<Tail...> {
    Head value;
public:
    Tuple() = default;
    Tuple(Head h, Tail... t) : Tuple<Tail...>(t...), value(h) {}

    Head get() const { return value; }
    Tuple<Tail...>& getTail() { return *this; }
    const Tuple<Tail...>& getTail() const { return *this; }
};

// Helper to get Nth element
template <size_t N, typename... Types>
auto get(const Tuple<Types...>& t) {
    if constexpr (N == 0) {
        return t.get();
    } else {
        return get<N-1>(t.getTail());
    }
}

void variadicDemo() {
    cout << "\n=== Variadic Templates ===" << endl;

    print(1, 2.5, "hello", 'c');
    print("Variadic", "templates", "are", "powerful");

    cout << "Sum: " << sum(1, 2, 3, 4, 5) << endl;
    cout << "Sum doubles: " << sum(1.1, 2.2, 3.3) << endl;

    Tuple<int, double, string> t(42, 3.14, "hello");
    cout << "Tuple[0]: " << get<0>(t) << endl;
    cout << "Tuple[1]: " << get<1>(t) << endl;
    cout << "Tuple[2]: " << get<2>(t) << endl;
}

// ============================================
// TEMPLATE SPECIALIZATION
// ============================================

template <typename T>
class Processor {
public:
    void process(T value) { cout << "General: " << value << endl; }
};

// Full specialization for int
template <>
class Processor<int> {
public:
    void process(int value) { cout << "Specialized for int: " << value * 2 << endl; }
};

// Partial specialization for pointers
template <typename T>
class Processor<T*> {
public:
    void process(T* value) {
        if (value) cout << "Pointer: " << *value << endl;
        else cout << "Null pointer" << endl;
    }
};

void specializationDemo() {
    cout << "\n=== Template Specialization ===" << endl;

    Processor<double> pd;
    pd.process(3.14);  // General

    Processor<int> pi;
    pi.process(5);  // Specialized

    int x = 10;
    Processor<int*> pp;
    pp.process(&x);  // Partial specialization
    pp.process(nullptr);
}

// ============================================
// SFINAE AND TYPE TRAITS
// ============================================

// Enable if (SFINAE)
template <typename T>
typename enable_if<is_integral<T>::value, T>::type
processIntegral(T value) {
    return value * 2;
}

template <typename T>
typename enable_if<is_floating_point<T>::value, T>::type
processIntegral(T value) {
    return value * 1.5;
}

// C++17 if constexpr
template <typename T>
auto processAuto(T value) {
    if constexpr (is_integral_v<T>) {
        return value * 2;
    } else if constexpr (is_floating_point_v<T>) {
        return value * 1.5;
    } else {
        return value;
    }
}

void sfinaeDemo() {
    cout << "\n=== SFINAE and Type Traits ===" << endl;

    cout << "processIntegral(5): " << processIntegral(5) << endl;
    cout << "processIntegral(3.0): " << processIntegral(3.0) << endl;

    cout << "processAuto(5): " << processAuto(5) << endl;
    cout << "processAuto(3.0): " << processAuto(3.0) << endl;
    cout << "processAuto('c'): " << processAuto('c') << endl;
}

int main() {
    functionTemplatesDemo();
    classTemplatesDemo();
    nonTypeParamsDemo();
    defaultParamsDemo();
    staticMembersDemo();
    inheritanceDemo();
    variadicDemo();
    specializationDemo();
    sfinaeDemo();

    return 0;
}