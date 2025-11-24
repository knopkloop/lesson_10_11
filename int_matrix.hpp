#ifndef INT_MATRIX_HPP
#define INT_MATRIX_HPP
#include <iostream>
#include "int_array.hpp"
struct IntMatrix
{
  IntArray matrix = IntArray(0, 0);
  size_t rows = 0;
  size_t cols = 0;
  
  std::istream &readMatrix(std::istream &in);
  int get(size_t i, size_t j) const;
  void set(size_t i, size_t j, int v);
  void addCol(size_t num, size_t val);
  void addZeroRowAndCol(size_t num_r, size_t num_c);
  void writeMatrix() const noexcept;
};
#endif
