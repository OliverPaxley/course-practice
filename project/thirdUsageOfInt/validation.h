#ifndef VALIDATION_H
#define VALIDATION_H
#include <iostream>
class Validation {
protected:
    int noOfValidation{};
public:
    virtual bool operator()(int val, std::string& messageOut) = 0;
};
class noValidation :public Validation {
public:
    bool operator()(int val, std::string& messageOut){ return true; };
};
class ValidAge : public Validation {
    int m_minAge;
    int m_maxAge;
public:
    ValidAge(int min = 19, int max = 100);
    bool operator()(int val, std::string& messageOut);
};
class validMark : public Validation {
public:
    bool operator()(int val, std::string& messageOut);
};
#endif