#include <iostream>
#include <fstream>

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
  size_t getsize() const noexcept;
  int last() const noexcept;
};

struct IntMatrix
{
  IntArray matrix = IntArray(0, 0);
  size_t rows = 0;
  size_t cols = 0;
  
  std::istream &readMatrix(std::istream &in);
  int *addRow(size_t num, int val) const;
  int *addZeroRowAndCol(size_t num_r, size_t num_c);
  void writeMatrix() const noexcept;
};


int main(int argc, const char **argv)
{
  std::cout << "Hello, world\n";
  return 0;
}

IntArray::~IntArray()
{
  delete[] data;
}

IntArray::IntArray(size_t k, int i):
  data(new int[k]),
  size(k)
{
  for (size_t j = 0; j < k; ++j)
  {
    data[j] = i;
  }
}

IntArray::IntArray(const IntArray &rhs):
  data(new int[rhs.getsize()]),
  size(rhs.getsize())
{
  for (size_t i = 0; i < rhs.getsize(); ++i)
  {
    data[i] = rhs.get(i);
  }
}

IntArray &IntArray::operator = (const IntArray &rhs)
{
  size = rhs.getsize();
  int *temp = new int [rhs.getsize()];
  for(size_t i = 0; i < rhs.getsize(); ++i)
  {
    temp[i] = rhs.get(i);
  }
  delete[] data;
  data = temp;
  size = rhs.getsize();
  return *this;
}

IntArray::IntArray(IntArray &&rhs):
data(rhs.data),
size(rhs.getsize())
{
  rhs.data = nullptr;
}

IntArray &IntArray::operator = (IntArray &&rhs)
{
  delete[] data;
  data = rhs.data;
  size = rhs.getsize();

  rhs.data = nullptr;
  return *this;
}

int IntArray::get(size_t id) const noexcept
{
  return data[id];
}

size_t IntArray::getsize() const noexcept
{
  return size;
}

int IntArray::last() const noexcept
{
  return get(getsize() - 1);
}

void IntArray::add(int i)
{
  int *temp = new int[getsize() + 1];
  for (size_t j = 0; j < getsize(); ++j)
  {
    temp[j] = get(j);
  }
  temp[getsize()] = i;
  delete[] data;
  data = temp;
  ++size;
}
