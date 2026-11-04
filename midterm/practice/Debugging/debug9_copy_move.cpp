// Debugging Practice 9 - Copy vs Move Semantics
// Predict the EXACT output (no newlines) or "Fails to Compile"

#include <iostream>
#include <utility>

using namespace std;

class Test {
    int* data;
    int size;
public:
    Test(int s = 5) : size(s), data(new int[s]) {
        for (int i = 0; i < size; ++i) data[i] = i;
        cout << "Ctor";
    }
    Test(const Test& other) : size(other.size), data(new int[other.size]) {
        for (int i = 0; i < size; ++i) data[i] = other.data[i];
        cout << "Copy";
    }
    Test(Test&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "Move";
    }
    ~Test() { delete[] data; }
};

int main() {
    Test a(3);
    Test b = a;
    Test c = std::move(a);
    return 0;
}

/*
Expected Output: CtorCopyMove
Explanation: a constructed (Ctor), b copy constructed from a (Copy), c move constructed from a (Move)
*/