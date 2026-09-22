#include <iostream>
#include <string>
using namespace std;

class Item {
    int id{};                  // default initializer
    string name{ "empty" };    // default initializer
public:
    Item() = default ;                        // uses defaults
    Item(const string& n) : name(n) {};     // member list
    Item(const string& n, int i) : id(i), name(n) {};
    void display() const {
        cout << name << " : " << id << endl; 
    }
};

int main() {
   Item a ,b("apple"), c{ "grape", 6 };
   a.display();
   b.display();
   c.display();
   return 0;
}