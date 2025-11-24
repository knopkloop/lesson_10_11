#include "int_matrix.hpp"
#include <iostream>

std::istream &IntMatrix::readMatrix(std::istream &in)
{
  in >> rows >> cols;
  if (!in)
  {
    throw std::logic_error("Unexpected input for rows/cols");
  }
  else if (rows <= 0 || cols <= 0)
  {
    throw std::logic_error("Invalid value for rows/cols");
  }
  
  try
  {
    delete[] matrix.data;
    matrix.data = new int[rows * cols];
    matrix.size = rows * cols;
  }
  catch (const std::bad_alloc &)
  {
    matrix.data = nullptr;
    matrix.size = 0;
    rows = 0;
    cols = 0;
    throw;
  }
  
  for (size_t ind = 0; ind < matrix.size; ++ind)
  {
    in >> matrix.data[ind];
    if (!in)
    {
      delete[] matrix.data;
      matrix.data = nullptr;
      matrix.size = 0;
      rows = 0;
      cols = 0;
      throw std::logic_error("Matrix reading error");
    }
  }
  return in;
}

int IntMatrix::get(size_t i, size_t j) const
{
  return matrix.get(i * cols + j);
}

void IntMatrix::set(size_t i, size_t j, int v)
{
  matrix.set(i * cols + j, v);
}

void IntMatrix::addCol(size_t num_c, size_t val)
{
  if (num_c > cols)
  {
    throw std::logic_error("In matrix there isn't enough cols");
  }
  
  int *temp = nullptr;
  try
  {
    temp = new int[rows * (cols + 1)];
  }
  catch (const std::bad_alloc &)
  {
    throw;
  }
  
  for (size_t i = 0; i < rows; ++i)
  {
  
    for (size_t j = 0; j < num_c; ++j)
    {
      temp[i * (cols + 1) + j] = get(i, j);
    }
    
    temp[i * (cols + 1) + num_c] = val;
    
    for (size_t j = num_c; j < cols; ++j)
    {
      temp[i * (cols + 1) + j + 1] = get(i, j);
    }
  }
  
  delete[] matrix.data;
  matrix.data = temp;
  ++cols;
  matrix.size = rows * cols;
}
  
void IntMatrix::addZeroRowAndCol(size_t num_r, size_t num_c)
{
  if (num_r > rows)
  {
    throw std::logic_error("There isn't enough rows in matrix");
  }
  if (num_c > cols)
  {
    throw std::logic_error("There isn't enough cols in matrix");
  }
  
  int *temp = nullptr;
  try
  {
    temp = new int[(rows + 1) * (cols + 1)];
    for (size_t ind = 0; ind < (rows + 1) * (cols + 1); ++ind)
    {
      temp[ind] = 0;
    }
  }
  catch (const std::bad_alloc &)
  {
    throw;
  }
  
  size_t temp_i = 0, temp_j = 0;
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      temp_i = i < num_r ? i : i + 1;
      temp_j = j < num_c ? j : j + 1;
      temp[temp_i * (cols + 1) + temp_j] = get(i, j);
    }
  }
  
  delete[] matrix.data;
  matrix.data = temp;
  ++cols;
  ++rows;
  matrix.size = rows * cols;
}
 
void IntMatrix::writeMatrix() const noexcept
{
  std::cout << "\n";
  
  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols - 1; ++j)
    {
      std::cout << matrix.data[i * cols + j] << " ";
    }
    std::cout << matrix.data[i * cols + (cols - 1)] << "\n";
  }
  std::cout << "\n";
}
