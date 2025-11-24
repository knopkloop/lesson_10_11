#include <iostream>
#include <fstream>
#include "int_array.hpp"
#include "int_matrix.hpp"

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
          try
          {
          arr.addCol(n1, n2);
          }
          catch (const std::logic_error &e)
          {
            std::cerr << e.what() << "\n";
            return 1;
          }
          catch (const std::bad_alloc&)
          {
            std::cerr << "Memory allocation error" << "\n";
            return 2;
          }
          arr.writeMatrix();
          break;
        case 3:
          try
          {
            arr.addZeroRowAndCol(n1, n2);
          }
          catch (const std::logic_error &e)
          {
            std::cerr << e.what() << "\n";
            return 1;
          }
          catch (const std::bad_alloc&)
          {
            std::cerr << "Memory allocation error" << "\n";
            return 2;
          }
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

