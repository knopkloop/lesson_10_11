#include <iostream>

struct IntArray
{
  int *data;
  size_t size;
  
  IntArray(int i);
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

int main(int argc, const char **argv)
{
  std::cout << "Hello, world\n";
  return 0;
}

IntArray::~IntArray()
{
  delete[] data;
}

IntArray::IntArray(int i):
  data(new int[1]),
  size(1)
{
  *data = i;
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
