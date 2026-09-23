#include "IntArray.h"
namespace seneca {
    IntArray::IntArray(size_t size) {
        if (size) {
            m_elements = new int[m_size = size] {};
        }
    }
    IntArray::IntArray(const int vals[], size_t size) {
        if (size && vals) {
            m_elements = new int[m_size = size];
            for (size_t i = 0; i < size; i++) {
                m_elements[i] = vals[i];
            }
        }
    }

    IntArray::IntArray(const IntArray& other) {
        if (other.size() && other.m_elements) {
            m_elements = new int[m_size = other.m_size];
            for (size_t i = 0; i < m_size; i++) {
                m_elements[i] = other.m_elements[i];
            }
        }
    }

    IntArray::IntArray(IntArray&& other) noexcept{
        m_elements = other.m_elements;
        m_size = other.m_size;
        other.m_elements = nullptr;
        other.m_size = 0;
    }

    IntArray& IntArray::operator=(const IntArray& other) {
        setEmpty();
        if (other.size() && other.m_elements) {
            m_elements = new int[m_size = other.m_size];
            for (size_t i = 0; i < m_size; i++) {
                m_elements[i] = other.m_elements[i];
            }
        }
        return *this;
    }

    IntArray& IntArray::operator=(IntArray&& other) noexcept {
        setEmpty();
        m_elements = other.m_elements;
        m_size = other.m_size;
        other.m_elements = nullptr;
        other.m_size = 0;
        return *this;
    }

    int& IntArray::operator[](size_t index) {
        return m_elements[index % m_size];
    }

    const int& IntArray::operator[](size_t index) const {
        return m_elements[index % m_size];
    }

    void IntArray::setEmpty() {
        delete[] m_elements;
        m_size = 0;
    }

    bool IntArray::isEmpty() const {
        return !m_elements;
    }

    IntArray::operator bool() const {
        return !!m_elements;
    }

    size_t IntArray::size() const {
        return m_size;
    }

    IntArray::~IntArray() {
        delete[] m_elements;
    }
}