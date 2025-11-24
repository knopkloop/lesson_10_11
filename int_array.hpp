#ifndef INT_ARRAY_HPP
#define INT_ARRAY_HPP
#include <iostream>
struct IntArray
{
  int *data;
  size_t size;

  IntArray(size_t k, int i);
  ~IntArray();
  IntArray(const IntArray &rhs);
  IntArray &operator = (const IntArray &rhs);
  IntArray(IntArray &&rhs);
  IntArray &operator = (IntArray &&rhs);

  void add(int i);
  int get(size_t id) const noexcept;
  void set(size_t id, int v);
  size_t getsize() const noexcept;
  int last() const noexcept;
};
#endif
