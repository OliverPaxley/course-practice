#ifndef INT_H
#define INT_H
#include <iostream>
#include "validation.h"

class Int {
    int m_value{};
    std::string m_message{""};
    Validation* m_valid;
public:
    Int(int value = 0, Validation* validationFactor = nullptr);
    void set(Validation* validationFactor = nullptr);
    auto get(std::istream& istr)->std::istream&;
    auto put(std::ostream& ostr) const->std::ostream&;
};
std::ostream& operator<<(std::ostream& ostr,const Int& I);
std::istream& operator>>(std::istream& istr, Int& I );

#endif