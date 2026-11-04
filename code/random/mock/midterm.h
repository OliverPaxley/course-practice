#ifndef MIDTERM_H
#define MIDTERM_H
#include <iostream>
#include <cstring>
#include <string>
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
                m_len = std::strlen(text);
                m_text = new char[m_len + 1];
                std::memcpy(m_text, text, m_len + 1);
            }
        };
        Message(const Message& src) : m_len{src.m_len} {
            if (src.m_text) {
                m_text = new char[m_len + 1];
                std::memcpy(m_text, src.m_text, m_len + 1);
            }
        }
        Message& operator=(const Message& src) {
            if (this != &src) {
                Message copy(src);
                swap(copy);
            }
            return *this;
        }
        Message(Message&& src) noexcept : m_text{src.m_text}, m_len{src.m_len} {
            src.m_text = nullptr;
            src.m_len = 0;
        }
        Message& operator=(Message&& src)noexcept {
            if (this != &src) {
                delete[] m_text;
                m_text = src.m_text;
                m_len = src.m_len;
                src.m_text = nullptr;
                src.m_len = 0;
            }
            return *this;
        }
        void swap(Message& other) noexcept {
            char* text = m_text;
            m_text = other.m_text;
            other.m_text = text;
            size_t len = m_len;
            m_len = other.m_len;
            other.m_len = len;
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
        Vehicle(const std::string& plate) : m_plate{plate} {}
        virtual double toll() const { return 0.0; }
        virtual std::ostream& display(std::ostream& os) const { return os << "Vehicle " << m_plate; }
        virtual ~Vehicle() = default ;
    };
    class Car : public Vehicle {
        int m_passenger{};
    public:
        Car(const std::string& plate, int passenger) : Vehicle(plate), m_passenger(passenger) {}
        double toll() const override {
            const int extraPassengers = m_passenger > 2 ? m_passenger - 2 : 0;
            return 2.50 + 0.50 * static_cast<double>(extraPassengers);
        }
        std::ostream& display(std::ostream& os) const override {
            return os << "Car " << m_plate << ": " << m_passenger << " passengers";
        }
    };
    class Truck : public Vehicle {
        size_t m_axles{};
    public:
        Truck(const std::string& plate, size_t axles) : Vehicle(plate), m_axles(axles) {}
        double toll() const override {
            return 4.00 * static_cast<double>(m_axles);
        }
        std::ostream& display(std::ostream& os) const override {
            return os << "Truck: " << m_plate << " " << m_axles << " axles";
        }
    };
    inline double totalToll(const seneca::Vehicle* const vehicles[], size_t count) {
        double total{};
        for (size_t i = 0; i < count; i++) {
            if (vehicles[i]) total += vehicles[i]->toll();
        }
        return total;
    }
    inline void printAll(const seneca::Vehicle* const vehicles[], size_t count, std::ostream& os){ 
        for (size_t i = 0; i< count; i++) {
            if (vehicles[i]) vehicles[i]->display(os) << '\n';
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
        Cars(const Engine& E) : Engine(E), m_engine(new Engine(E)) {}
        Cars(const Cars& src)
            : Engine(src), m_engine(src.m_engine ? new Engine(*src.m_engine) : nullptr) {}
        Cars& operator=(const Cars&) = delete;
        ~Cars() { delete m_engine; }
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
        ~Garage() = default; // The Car objects are owned elsewhere.
    };
    // Question 4: Function pointers and lambdas (16 marks)
    using Condition = bool(*)(int);
    inline int countIf(const int arr[], size_t size, Condition cond) {
        if (!arr || !cond) return 0;
        int count{};
        for (size_t i = 0; i < size; ++i) {
            if (cond(arr[i])) {
                ++count;
            }
        }
        return count;
    }
    inline int filter(const int input[], size_t size, int output[], Condition cond) {
        if (!input || !output || !cond) return 0;
        int copied{};
        for (size_t i = 0; i < size; ++i) {
            if (cond(input[i])) {
                output[copied++] = input[i];
            }
        }
        return copied;
    }
    inline bool isPrime(int value) {
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
