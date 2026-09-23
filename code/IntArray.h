#ifndef SENECA_INTARRAY_H
#define SENECA_INTARRAY_H
#include <cstddef>
namespace seneca {
   class IntArray {
      int* m_elements{};
      size_t m_size{};
   public:
      IntArray() = default;
      IntArray(size_t size);
      IntArray(const int vals[], size_t size);
      IntArray(const IntArray& other);// copy constructor
      IntArray(IntArray&& other)noexcept;// move constructor
      IntArray& operator=(const IntArray& other);// copy assignment
      IntArray& operator=(IntArray&& other)noexcept;// move assignment
      int& operator[](size_t index);
      const int& operator[](size_t index)const;
      void setEmpty();
      bool isEmpty()const;
      operator bool()const;
      size_t size()const;
      virtual ~IntArray();
   };
}
#endif // !SENENCA_INTARRAY_H

