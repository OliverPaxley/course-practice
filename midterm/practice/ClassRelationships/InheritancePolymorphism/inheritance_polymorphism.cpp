// Inheritance and Inclusion Polymorphism - Practice Code for Midterm
// Topics: Abstract/concrete classes, virtual functions, pure virtual, cloning, dynamic_cast, RTTI, LSP

#include <iostream>
#include <string>
#include <typeinfo>
#include <memory>
#include <vector>

using namespace std;

// ============================================
// ABSTRACT BASE CLASS
// ============================================

class Shape {
public:
    virtual ~Shape() = default;  // Virtual destructor essential!

    // Pure virtual function - makes class abstract
    virtual double volume() const = 0;
    virtual double surfaceArea() const = 0;

    // Virtual function with default implementation
    virtual void printInfo() const {
        cout << "Shape: volume=" << volume()
             << ", area=" << surfaceArea() << endl;
    }

    // Cloning pattern for polymorphic copying
    virtual Shape* clone() const = 0;
};

// ============================================
// CONCRETE DERIVED CLASSES
// ============================================

class Cube : public Shape {
    double len;
public:
    Cube(double l = 1.0) : len(l) {}

    double volume() const override { return len * len * len; }
    double surfaceArea() const override { return 6 * len * len; }

    void printInfo() const override {
        cout << "Cube: len=" << len
             << ", volume=" << volume()
             << ", area=" << surfaceArea() << endl;
    }

    Shape* clone() const override { return new Cube(*this); }

    double getLen() const { return len; }
};

class Sphere : public Shape {
    double rad;
    static constexpr double PI = 3.14159265359;
public:
    Sphere(double r = 1.0) : rad(r) {}

    double volume() const override { return 4.0/3.0 * PI * rad * rad * rad; }
    double surfaceArea() const override { return 4 * PI * rad * rad; }

    void printInfo() const override {
        cout << "Sphere: rad=" << rad
             << ", volume=" << volume()
             << ", area=" << surfaceArea() << endl;
    }

    Shape* clone() const override { return new Sphere(*this); }

    double getRad() const { return rad; }
};

class Cylinder : public Shape {
    double rad, height;
    static constexpr double PI = 3.14159265359;
public:
    Cylinder(double r = 1.0, double h = 1.0) : rad(r), height(h) {}

    double volume() const override { return PI * rad * rad * height; }
    double surfaceArea() const override { return 2 * PI * rad * (rad + height); }

    void printInfo() const override {
        cout << "Cylinder: rad=" << rad << ", h=" << height
             << ", volume=" << volume()
             << ", area=" << surfaceArea() << endl;
    }

    Shape* clone() const override { return new Cylinder(*this); }
};

// ============================================
// INCLUSION POLYMORPHISM
// ============================================

void displayVolume(const Shape& s) {
    cout << "Volume: " << s.volume() << endl;
}

void processShapes(const vector<Shape*>& shapes) {
    for (const auto* s : shapes) {
        s->printInfo();
    }
}

// Polymorphic copying via clone
vector<Shape*> cloneShapes(const vector<Shape*>& originals) {
    vector<Shape*> copies;
    for (const auto* s : originals) {
        copies.push_back(s->clone());
    }
    return copies;
}

// ============================================
// DYNAMIC CAST
// ============================================

void dynamicCastDemo() {
    cout << "\n=== Dynamic Cast ===" << endl;

    Shape* shapes[] = {new Cube(3), new Sphere(2), new Cylinder(2, 5)};

    for (Shape* s : shapes) {
        // Try to cast to Cube
        Cube* c = dynamic_cast<Cube*>(s);
        if (c) {
            cout << "Found Cube with len=" << c->getLen() << endl;
        }

        // Try to cast to Sphere
        Sphere* sp = dynamic_cast<Sphere*>(s);
        if (sp) {
            cout << "Found Sphere with rad=" << sp->getRad() << endl;
        }

        // Reference version (throws bad_cast on failure)
        try {
            Cube& cRef = dynamic_cast<Cube&>(*s);
            cout << "Reference cast to Cube: len=" << cRef.getLen() << endl;
        } catch (const bad_cast&) {
            // Not a Cube
        }
    }

    // Cleanup
    for (Shape* s : shapes) delete s;
}

// ============================================
// RTTI (Run-Time Type Information)
// ============================================

void rttiDemo() {
    cout << "\n=== RTTI ===" << endl;

    Shape* s1 = new Cube(3);
    Shape* s2 = new Sphere(2);

    // typeid on pointer gives static type
    cout << "typeid(s1).name(): " << typeid(s1).name() << endl;  // Shape*

    // typeid on dereferenced pointer gives dynamic type
    cout << "typeid(*s1).name(): " << typeid(*s1).name() << endl;  // Cube
    cout << "typeid(*s2).name(): " << typeid(*s2).name() << endl;  // Sphere

    // Compare types
    if (typeid(*s1) == typeid(*s2)) {
        cout << "Same type" << endl;
    } else {
        cout << "Different types" << endl;
    }

    // type_info::before for ordering (implementation-defined)
    cout << "typeid(*s1).before(typeid(*s2)): "
         << typeid(*s1).before(typeid(*s2)) << endl;

    delete s1;
    delete s2;
}

// ============================================
// LISKOV SUBSTITUTION PRINCIPLE (LSP)
// ============================================

// CORRECT DESIGN: Rectangle from Square
// Square is more abstract (one dimension), Rectangle adds height

class SquareLSP {
    double width;
public:
    SquareLSP(double w = 1.0) : width(w) {}
    virtual void setWidth(double w) { width = w; }
    double getWidth() const { return width; }
    virtual double area() const { return width * width; }
};

class RectangleLSP : public SquareLSP {
    double height;
public:
    RectangleLSP(double w = 1.0, double h = 1.0)
        : SquareLSP(w), height(h) {}
    void setHeight(double h) { height = h; }
    double getHeight() const { return height; }
    double area() const override { return getWidth() * height; }
};

void useSquare(SquareLSP& s) {
    s.setWidth(5);
    // Expects square behavior: width == height
    cout << "Width: " << s.getWidth() << ", Area: " << s.area() << endl;
}

void lspCorrectDemo() {
    cout << "\n=== LSP Correct: Rectangle from Square ===" << endl;

    SquareLSP sq(3);
    useSquare(sq);  // Works: area = 25

    RectangleLSP rect(3, 4);
    useSquare(rect);  // Works: area = 20 (rectangle behavior)
}

// INCORRECT DESIGN: Square from Rectangle (violates LSP)

class RectangleBad {
protected:
    double width, height;
public:
    RectangleBad(double w = 1.0, double h = 1.0) : width(w), height(h) {}
    virtual void setWidth(double w) { width = w; }
    virtual void setHeight(double h) { height = h; }
    double getWidth() const { return width; }
    double getHeight() const { return height; }
    double area() const { return width * height; }
};

class SquareBad : public RectangleBad {
public:
    SquareBad(double s = 1.0) : RectangleBad(s, s) {}

    // Override to maintain square invariant
    void setWidth(double s) override {
        RectangleBad::setWidth(s);
        RectangleBad::setHeight(s);  // Forces equal sides
    }
    void setHeight(double s) override {
        RectangleBad::setWidth(s);
        RectangleBad::setHeight(s);
    }
};

void useRectangle(const RectangleBad& r) {
    // Expects independent width/height
    const_cast<RectangleBad&>(r).setWidth(5);
    const_cast<RectangleBad&>(r).setHeight(3);
    cout << "Width: " << r.getWidth() << ", Height: " << r.getHeight()
         << ", Area: " << r.area() << endl;
}

void lspIncorrectDemo() {
    cout << "\n=== LSP Incorrect: Square from Rectangle ===" << endl;

    RectangleBad rect(4, 3);
    useRectangle(rect);  // Works: width=5, height=3, area=15

    SquareBad sq(4);
    useRectangle(sq);    // BROKEN: width=3, height=3, area=9!
    // Square cannot maintain invariant when used as Rectangle
}

// ============================================
// VIRTUAL DESTRUCTOR IMPORTANCE
// ============================================

class BaseNoVirtual {
public:
    BaseNoVirtual() { cout << "BaseNoVirtual ctor" << endl; }
    ~BaseNoVirtual() { cout << "BaseNoVirtual dtor" << endl; }
};

class DerivedNoVirtual : public BaseNoVirtual {
    int* data;
public:
    DerivedNoVirtual() : data(new int[100]) { cout << "DerivedNoVirtual ctor" << endl; }
    ~DerivedNoVirtual() { delete[] data; cout << "DerivedNoVirtual dtor" << endl; }
};

class BaseVirtual {
public:
    BaseVirtual() { cout << "BaseVirtual ctor" << endl; }
    virtual ~BaseVirtual() { cout << "BaseVirtual dtor" << endl; }
};

class DerivedVirtual : public BaseVirtual {
    int* data;
public:
    DerivedVirtual() : data(new int[100]) { cout << "DerivedVirtual ctor" << endl; }
    ~DerivedVirtual() { delete[] data; cout << "DerivedVirtual dtor" << endl; }
};

void virtualDestructorDemo() {
    cout << "\n=== Virtual Destructor Importance ===" << endl;

    cout << "--- Without virtual destructor ---" << endl;
    BaseNoVirtual* b1 = new DerivedNoVirtual();
    delete b1;  // Only BaseNoVirtual dtor called! Memory leak!

    cout << "\n--- With virtual destructor ---" << endl;
    BaseVirtual* b2 = new DerivedVirtual();
    delete b2;  // Both destructors called correctly
}

// ============================================
// OVERRIDE AND FINAL
// ============================================

class BaseOverride {
public:
    virtual void func(int) { cout << "Base::func(int)" << endl; }
    virtual void func2() { cout << "Base::func2()" << endl; }
    virtual void func3() final { cout << "Base::func3() final" << endl; }
};

class DerivedOverride : public BaseOverride {
public:
    void func(int) override { cout << "Derived::func(int)" << endl; }  // OK
    // void func(double) override { }  // ERROR: no matching virtual
    void func2() override { cout << "Derived::func2()" << endl; }    // OK
    // void func3() override { }       // ERROR: func3 is final
};

class FurtherDerived : public DerivedOverride {
public:
    // void func3() override { }  // ERROR: func3 is final in BaseOverride
};

int main() {
    // Basic polymorphism
    Cube cube(3);
    Sphere sphere(2);

    displayVolume(cube);   // 27
    displayVolume(sphere); // ~33.51

    vector<Shape*> shapes = {new Cube(2), new Sphere(3), new Cylinder(1, 4)};
    processShapes(shapes);

    // Cloning
    auto copies = cloneShapes(shapes);
    cout << "\nCloned shapes:" << endl;
    processShapes(copies);

    // Cleanup
    for (auto* s : shapes) delete s;
    for (auto* s : copies) delete s;

    // Dynamic cast
    dynamicCastDemo();

    // RTTI
    rttiDemo();

    // LSP
    lspCorrectDemo();
    lspIncorrectDemo();

    // Virtual destructor
    virtualDestructorDemo();

    // Override/final
    DerivedOverride d;
    d.func(1);
    d.func2();
    d.func3();

    return 0;
}