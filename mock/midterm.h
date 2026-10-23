#ifndef MIDTERM_H
#define MIDTERM_H
#include <iostream>
#include <cstring>
using namespace std;

namespace seneca {
    // Question 1: Resource management (18 marks)
    class Message {
        char* m_text{};      // dynamically allocated C-string
        size_t m_len{};
    public:
        Message() = default;
        Message(const char* text) {
            if (text) {
                m_text = new char[strlen(text) + 1];
                strcpy(m_text, text);
            }
        };
        Message(const Message& src) =default;
        Message& operator=(const Message& src)= default;
        Message(Message&& src)noexcept : m_text{src.m_text}, m_len(src.m_len) {
            delete[] src.m_text;
            src.m_len = 0;
        }
        Message& operator=(Message&& src)noexcept {
            if (this != &src) {
                delete[] m_text;
                m_text = nullptr;
                m_text = src.m_text;
                m_len = src.m_len;
                delete[] src.m_text;
                src.m_len = 0;
            }
            return *this;
        }
        ~Message() {
            delete[] m_text;
        }
    };
    // Question 2: Inheritance and polymorphism (18 marks)
    class Vehicle {
    protected:
        std::string m_plate;
    public:
        Vehicle(const std::string& plate) : m_plate{plate}{};
        virtual double toll() const;
        virtual std::ostream& display(std::ostream&) const;
        virtual ~Vehicle() = default ;
    };
    class Car : public Vehicle {
        size_t m_passenger{};
    public:
        Car(const std::string& plate ,size_t passenger) : Vehicle(plate), m_passenger(passenger){};
        double toll() const override {
            return 2.5 + 0.5*static_cast<double>(m_passenger);
        }
        std::ostream& display(std::ostream&) const override {
            cout << "Car : " << m_plate << " Passenger: " << m_passenger << endl ;
            return cout;
        }
    };
    class Truck : public Vehicle {
        size_t m_axles{};
    public:
        Truck(std::string& plate, size_t axles) : Vehicle(plate), m_axles(axles){};
        double toll() const override {
            return 4.00 * static_cast<double>(m_axles);
        }
        std::ostream& display(std::ostream&) const override {
            cout << "Truck: " << m_plate << " " << m_axles << " axles " << endl;
            return cout;
        }
    };
    double totalToll(const seneca::Vehicle* const vehicles[], size_t count) {
        double total{};
        for (size_t i = 0; i < count; i++) {
            total += vehicles[i]->toll();
        }
        return total;
    }
    void printAll(const seneca::Vehicle* const vehicles[], size_t count, std::ostream& os){ 
        for (size_t i = 0; i< count; i++) {
            vehicles[i]->display(os);
        }
    }
    // Question 3: Class templates and relationships (18 marks)
    // Part A: Template (10 marks)
    template<typename T, size_t CAP>
    class Stack {
        T m_data[CAP]{};
        size_t m_count{};
    public:
        bool push(const T& item);   // false if full
        bool pop(T& out);           // removes top into out; false if empty
        const T& top() const;       // returns top; if empty, returns m_data[0]
        size_t size() const;
        bool empty() const;
    };
    template<typename T, size_t CAP>
    bool Stack<T,CAP>::push(const T& item) {
        if (m_count == CAP) {
            return false;
        }
        m_data[m_count++] = item;
        return true;
    }
    template<typename T, size_t CAP>
    bool Stack<T, CAP>::pop(T& out) {
        if (m_count == 0) {
            return false;
        }
        out = m_data[--m_count];
        return true;
    }
    template<typename T, size_t CAP>
    const T& Stack<T, CAP>::top() const {
        return m_count == 0 ? m_data[0] : m_data[m_count - 1];
    }
    template<typename T, size_t CAP>
    size_t Stack<T, CAP>::size() const {
        return m_count;
    }
    template<typename T, size_t CAP>
    bool Stack<T, CAP>::empty() const {
        return m_count == 0;
    }
    // Part B: Relationships (8 marks)
    class Engine { /* assume complete, has copy ctor */ };
    class Driver { /* assume complete */ };

    class Cars : public Engine {
        Engine* m_engine{};
    public:
        Cars(const Engine& E) : Engine(E), m_engine(new Engine(E)) {};
    };
    class Garage : public Cars {
        Car* m_cars[5]{};
        size_t m_count{};
    public:
        Garage(Car* c) : Cars(Engine{}) {
            *this += c;
        }
        Garage& operator+=(Car* c) {
            if (c && m_count < 5) {
                m_cars[m_count++] = c;
            }
            return *this;
        }
        ~Garage() {
            // Cars are owned elsewhere, so do not delete them here.
        }
    };
    // Question 4: Function pointers and lambdas (16 marks)
    using Condition = bool(*)(int);
    int countIf(const int arr[], size_t size, Condition cond) {
        int count{};
        for (size_t i = 0; i < size; ++i) {
            if (cond(arr[i])) {
                ++count;
            }
        }
        return count;
    }
    int filter(const int input[], size_t size, int output[], Condition cond) {
        int copied{};
        for (size_t i = 0; i < size; ++i) {
            if (cond(input[i])) {
                output[copied++] = input[i];
            }
        }
        return copied;
    }
    bool isPrime(int value) {
        if (value < 2) {
            return false;
        }
        for (int divisor = 2; divisor <= value / divisor; ++divisor) {
            if (value % divisor == 0) {
                return false;
            }
        }
        return true;
    }
}


#endif
