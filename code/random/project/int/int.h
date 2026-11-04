#ifndef INT_H
#define INT_H
#include <iostream>

class Int {
    int m_value{};
    std::string m_message{""};
    // function declaration, with auto
    // the -> bool means that the functions specify that the return type used boolean
    auto valid()-> bool;
public:
    Int(int value = 0);
    // same with this the return type is istream and ostream;
    auto get(std::istream& istr)->std::istream&;
    auto get(std::ostream& ostr)->std::ostream&;
    auto put(std::ostream& ostr) const->std::ostream&;
};
auto operator<<(std::ostream& ostr, Int& I)->std::ostream&;
auto operator>>(std::istream& istr, Int& I)->std::istream&;

#endif