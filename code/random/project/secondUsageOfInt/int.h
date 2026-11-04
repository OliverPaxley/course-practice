#ifndef INT_H
#define INT_H
#include <iostream>

class Int {
    int m_value{};
    std::string m_message{""};
    /*
        means that the pointer of m_valid points to the a pointer of a function than the function.
        the functions take 2 parameters and return a boolean(either true or false).
        it's default value points to none of the functions
    */
    auto (*m_valid)(int val, std::string& messageOut)-> bool = nullptr;
public:
    /*
        in c++ auto usually means one of 2 things: 
        -  type deduction: let the compiler figure out the data type;
        -  trailing return type: write the function's return type after its parameter using ->
    */
    Int(int value = 0, auto (*validationLogicAddress)(int val, std::string& messageOut)-> bool = nullptr);
    void set(auto (*validationLogicAddress)(int val, std::string& messageOut)-> bool);
    auto get(std::istream& istr)->std::istream&;
    auto put(std::ostream& ostr) const->std::ostream&;
};
auto operator<<(std::ostream& ostr, const Int& I)->std::ostream&;
auto operator>>(std::istream& istr, Int& I)->std::istream&;

#endif