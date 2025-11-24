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
  void set(size_t id, int v);
  size_t getsize() const noexcept;
  int last() const noexcept;
};

struct IntMatrix
{
  IntArray matrix = IntArray(0, 0);
  size_t rows = 0;
  size_t cols = 0;
  
  std::istream &readMatrix(std::istream &in);
  int get(size_t i, size_t j) const;
  void set(size_t i, size_t j, int v);
  int addRow(size_t num, size_t val) const;
  int addZeroRowAndCol(size_t num_r, size_t num_c);
  void writeMatrix() const noexcept;
};


int main(int argc, const char **argv)
{
  if (argc != 2)
  {
    std::cerr << "ERROR: not enough number of arguments" << "\n";
    return 1;
  }
  
  try
  {
    IntMatrix arr;
  
    std::ifstream in(argv[1]);
    
    if(!in.is_open())
    {
      std::cerr << "Opening file error" << "\n";
      return 1;
    }
  
    try
    {
      arr.readMatrix(in);
    }
    catch(const std::logic_error &e)
    {
      std::cerr << e.what() << "\n";
      return 1;
    }
    catch(const std::bad_alloc &)
    {
      std::cerr << "Memory allocation error" << "\n";
      return 2;
    }
    
    int comm = 0;
    size_t n1 = 0, n2 = 0;
    while ((std::cin >> comm >> n1 >> n2) && !(std::cin.eof()))
    {
      switch (comm)
      {
        case 1:
          std::cout << "Not my variant hehe" << "\n";
          break;
        case 2:
          arr.addRow(n1, n2);
          arr.writeMatrix();
          break;
        case 3:
          arr.addZeroRowAndCol(n1, n2);
          arr.writeMatrix();
          break;
        default:
          std::cerr << "Incorrect command" << "\n";
          return 3;
      }
      if (std::cin.fail() && !std::cin.eof())
      {
        std::cerr << "Unexpected parameters" << "\n";
        return 3;
      }
    }
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Memory allocation error" << "\n";
    return 3;
  }
  
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

void IntArray::set(size_t id, int v)
{
  data[id] =  v;
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

std::istream &IntMatrix::readMatrix(std::istream &in)
{
  in >> rows >> cols;
  if (!in)
  {
    throw std::logic_error("Unexpected input for rows/cols");
  }
  else if (rows == 0 || cols == 0)
  {
    throw std::logic_error("Zero values for rows/cols");
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

void IntMatrix::writeMatrix() const noexcept
{
  std::cout << "\n;
  
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
