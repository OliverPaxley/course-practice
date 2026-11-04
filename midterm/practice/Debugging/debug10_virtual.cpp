// Debugging Practice 10 - Virtual Functions and Polymorphism
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>

using namespace std;

class Base {
public:
    virtual void func() { cout << "Base"; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void func() override { cout << "Derived"; }
};

int main() {
    Base* ptr = new Derived();
    ptr->func();
    delete ptr;
    return 0;
}

/*
Expected Output: Derived
Explanation: ptr points to Derived object, virtual function calls Derived::func()
*/