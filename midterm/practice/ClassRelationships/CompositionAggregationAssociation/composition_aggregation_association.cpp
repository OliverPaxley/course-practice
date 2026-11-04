// Composition, Aggregation, and Association - Practice Code for Midterm
// Topics: Composition (strong ownership), Aggregation (weak ownership), Association (no ownership)

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// ============================================
// COMPOSITION - Strong "has-a" relationship
// Composer OWNS component, controls lifetime
// Component cannot exist without composer
// ============================================

// Method 1: Composition via Subobject (Preferred)
class Engine {
    int horsepower;
public:
    Engine(int hp = 150) : horsepower(hp) {
        cout << "Engine constructed (" << hp << " HP)" << endl;
    }
    ~Engine() { cout << "Engine destroyed" << endl; }

    int getHP() const { return horsepower; }
    void start() { cout << "Engine started (" << horsepower << " HP)" << endl; }
};

class CarComposition {
    Engine engine;  // Subobject - automatic lifetime management
    string model;
public:
    CarComposition(const string& m, int hp) : engine(hp), model(m) {
        cout << "Car constructed: " << model << endl;
    }
    ~CarComposition() { cout << "Car destroyed: " << model << endl; }

    void start() {
        cout << model << " starting... ";
        engine.start();
    }

    // Compiler-generated copy/assignment/destructor work correctly!
    // Deep copy handled by Engine's copy semantics
};

// Method 2: Composition via Owning Pointer (when needed)
class Transmission {
    int gears;
public:
    Transmission(int g = 6) : gears(g) {
        cout << "Transmission constructed (" << g << " gears)" << endl;
    }
    ~Transmission() { cout << "Transmission destroyed" << endl; }

    int getGears() const { return gears; }
};

class CarPointerComposition {
    string model;
    Transmission* transmission;  // Owning pointer

public:
    CarPointerComposition(const string& m, int gears) : model(m), transmission(new Transmission(gears)) {
        cout << "CarPointerComposition constructed: " << model << endl;
    }

    // MUST implement Rule of 5 for owning pointer!
    CarPointerComposition(const CarPointerComposition& other)
        : model(other.model), transmission(new Transmission(*other.transmission)) {
        cout << "CarPointerComposition copy constructed" << endl;
    }

    CarPointerComposition& operator=(const CarPointerComposition& other) {
        if (this != &other) {
            model = other.model;
            delete transmission;
            transmission = new Transmission(*other.transmission);
        }
        return *this;
    }

    CarPointerComposition(CarPointerComposition&& other) noexcept
        : model(std::move(other.model)), transmission(other.transmission) {
        other.transmission = nullptr;
        cout << "CarPointerComposition move constructed" << endl;
    }

    CarPointerComposition& operator=(CarPointerComposition&& other) noexcept {
        if (this != &other) {
            model = std::move(other.model);
            delete transmission;
            transmission = other.transmission;
            other.transmission = nullptr;
        }
        return *this;
    }

    ~CarPointerComposition() {
        delete transmission;
        cout << "CarPointerComposition destroyed: " << model << endl;
    }

    void start() {
        cout << model << " starting with " << transmission->getGears() << "-speed transmission" << endl;
    }
};

// ============================================
// AGGREGATION - Weak "has-a" relationship
// Aggregator USES object but does NOT manage creation/destruction
// Objects survive aggregator destruction
// ============================================

class Driver {
    string name;
public:
    Driver(const string& n) : name(n) {
        cout << "Driver created: " << name << endl;
    }
    ~Driver() { cout << "Driver destroyed: " << name << endl; }

    const string& getName() const { return name; }
    void drive() { cout << name << " is driving" << endl; }
};

class CarAggregation {
    string model;
    vector<Driver*> drivers;  // Non-owning pointers
public:
    CarAggregation(const string& m) : model(m) {
        cout << "CarAggregation created: " << model << endl;
    }
    ~CarAggregation() {
        cout << "CarAggregation destroyed: " << model << endl;
        // Does NOT delete drivers!
    }

    void addDriver(Driver& d) {
        drivers.push_back(&d);
        cout << d.getName() << " added to " << model << endl;
    }

    void removeDriver(Driver& d) {
        auto it = find(drivers.begin(), drivers.end(), &d);
        if (it != drivers.end()) {
            drivers.erase(it);
            cout << d.getName() << " removed from " << model << endl;
        }
    }

    void listDrivers() const {
        cout << model << " drivers: ";
        for (const auto* d : drivers) cout << d->getName() << ' ';
        cout << endl;
    }
};

// ============================================
// ASSOCIATION - Weakest "uses-a" relationship
// No ownership; both classes independent and complete
// Often bidirectional
// ============================================

class Course;  // Forward declaration

class Student {
    string name;
    vector<Course*> courses;  // Non-owning
public:
    Student(const string& n) : name(n) {}
    ~Student() { cout << "Student destroyed: " << name << endl; }

    const string& getName() const { return name; }

    void enroll(Course& c);
    void drop(Course& c);
    void listCourses() const;
};

class Course {
    string name;
    vector<Student*> students;  // Non-owning, bidirectional
public:
    Course(const string& n) : name(n) {}
    ~Course() { cout << "Course destroyed: " << name << endl; }

    const string& getName() const { return name; }

    void addStudent(Student& s) {
        students.push_back(&s);
    }
    void removeStudent(Student& s) {
        auto it = find(students.begin(), students.end(), &s);
        if (it != students.end()) students.erase(it);
    }
    void listStudents() const {
        cout << name << " students: ";
        for (const auto* s : students) cout << s->getName() << ' ';
        cout << endl;
    }
};

void Student::enroll(Course& c) {
    courses.push_back(&c);
    c.addStudent(*this);
    cout << name << " enrolled in " << c.getName() << endl;
}

void Student::drop(Course& c) {
    auto it = find(courses.begin(), courses.end(), &c);
    if (it != courses.end()) courses.erase(it);
    c.removeStudent(*this);
    cout << name << " dropped " << c.getName() << endl;
}

void Student::listCourses() const {
    cout << name << " courses: ";
    for (const auto* c : courses) cout << c->getName() << ' ';
    cout << endl;
}

// ============================================
// COMPARISON DEMO
// ============================================

void compositionDemo() {
    cout << "=== COMPOSITION (Subobject) ===" << endl;
    {
        CarComposition car("Toyota", 200);
        car.start();
    }  // Engine automatically destroyed with Car
    cout << "--- Car out of scope ---" << endl;

    cout << "\n=== COMPOSITION (Owning Pointer) ===" << endl;
    {
        CarPointerComposition car("Honda", 6);
        car.start();

        // Copy test
        CarPointerComposition car2 = car;  // Deep copy
        car2.start();
    }  // Both destroyed, no memory leaks
    cout << "--- Cars out of scope ---" << endl;
}

void aggregationDemo() {
    cout << "\n=== AGGREGATION ===" << endl;
    {
        CarAggregation car("BMW");

        Driver d1("Alice");  // Created externally
        Driver d2("Bob");

        car.addDriver(d1);
        car.addDriver(d2);
        car.listDrivers();

        d1.drive();
        d2.drive();
    }  // Car destroyed, but drivers still alive!
    cout << "--- CarAggregation out of scope ---" << endl;
    cout << "Drivers still exist!" << endl;
}

void associationDemo() {
    cout << "\n=== ASSOCIATION ===" << endl;
    {
        Student s1("Alice");
        Student s2("Bob");
        Course c1("Math");
        Course c2("Physics");

        s1.enroll(c1);
        s1.enroll(c2);
        s2.enroll(c1);

        s1.listCourses();
        s2.listCourses();
        c1.listStudents();
        c2.listStudents();

        s1.drop(c1);
        c1.listStudents();
    }  // All destroyed independently
    cout << "--- All out of scope ---" << endl;
}

// ============================================
// SMART POINTER VERSIONS (Modern C++)
// ============================================

// Composition with unique_ptr (modern)
class ModernCar {
    string model;
    unique_ptr<Engine> engine;  // Exclusive ownership
public:
    ModernCar(const string& m, int hp) : model(m), engine(make_unique<Engine>(hp)) {}

    void start() {
        cout << model << " starting... ";
        engine->start();
    }

    // unique_ptr handles Rule of 5 automatically!
    // Movable but not copyable (exclusive ownership)
};

// Aggregation with shared_ptr (shared ownership)
class SharedDriver {
    string name;
public:
    SharedDriver(const string& n) : name(n) {}
    const string& getName() const { return name; }
};

class SharedCar {
    string model;
    vector<shared_ptr<SharedDriver>> drivers;  // Shared ownership
public:
    SharedCar(const string& m) : model(m) {}

    void addDriver(const shared_ptr<SharedDriver>& d) {
        drivers.push_back(d);
    }

    void listDrivers() const {
        cout << model << " shared drivers: ";
        for (const auto& d : drivers) cout << d->getName() << ' ';
        cout << endl;
    }
};

void smartPointerDemo() {
    cout << "\n=== SMART POINTER VERSIONS ===" << endl;

    // Modern composition
    {
        ModernCar car("Tesla", 500);
        car.start();
        // unique_ptr auto-deletes engine
    }

    // Shared ownership aggregation
    {
        auto d1 = make_shared<SharedDriver>("Charlie");
        auto d2 = make_shared<SharedDriver>("Diana");

        SharedCar car("SharedCar");
        car.addDriver(d1);
        car.addDriver(d2);
        car.listDrivers();

        // Drivers kept alive by shared_ptr
    }
    cout << "--- SharedCar out of scope, but drivers may persist ---" << endl;
}

// ============================================
// COUPLING COMPARISON
// ============================================

// Composition: HIGH coupling - changes to Engine interface require Car changes
// Aggregation: MEDIUM coupling - CarAggregation knows Driver interface
// Association: LOWEST coupling - Student and Course only know each other's interface

class EngineV2 {
    int hp;
    bool turbo;
public:
    EngineV2(int h, bool t) : hp(h), turbo(t) {}
    int getHP() const { return hp; }
    bool hasTurbo() const { return turbo; }
};

// Composition requires forwarding
class CarV2 {
    EngineV2 engine;
public:
    CarV2(int hp, bool turbo) : engine(hp, turbo) {}

    // Forwarding methods - coupling!
    int getHP() const { return engine.getHP(); }
    bool hasTurbo() const { return engine.hasTurbo(); }
};

void couplingDemo() {
    cout << "\n=== COUPLING COMPARISON ===" << endl;

    // Composition: High coupling - must forward interface
    CarV2 car(300, true);
    cout << "Car HP: " << car.getHP() << ", Turbo: " << car.hasTurbo() << endl;

    // Aggregation/Association: Low coupling - no forwarding needed
}

int main() {
    compositionDemo();
    aggregationDemo();
    associationDemo();
    smartPointerDemo();
    couplingDemo();

    return 0;
}