#include <iostream>
// Do yooowana build a snowmaaaan, do you want to code some stuffffff
// Custom array class to hold integers
// This isn"t rhetorical btw > how do you define a collection without using a predefined collection object
class IntArray
{
private:
  int *data;
  size_t size;
  bool IndexValid(int index) const
  {
    return index >= 0 && index < size;
  };

public:
  // Main Constructor
  IntArray(int initial_size) : size(initial_size)
  {
    std::cout << "Constructor\n";
    data = new int[initial_size];
  };

  // Deconstructor
  ~IntArray()
  {
    std::cout << "Deconstructor\n";
    if (data != nullptr)
    {
      delete[] data;
    }
  };

  // Copy Assignment Operator
  IntArray &operator=(const IntArray &other)
  {
    std::cout << "Copy Assigment Operator Constructor\n";
    if (this != &other)
    {
      // Generate a "deep copy"; I guess that means address + value
      size = other.size;
      for (int i = 0; i < size; i++)
      {
        data[i] = other.Get(i);
      }
    }
    return *this;
  }
  // Copy constructor
  IntArray(const IntArray &other) : size(other.size)
  {
    std::cout << "Copy Constructor\n";
    data = new int[size];
    for (int i = 0; i < size; i++)
    {
      data[i] = other.Get(i);
    }
  };

  // Move constructor
  IntArray(IntArray &&other) noexcept
  {
    std::cout << "Move Constructor\n";
    size = other.size;
    data = std::move(other.data);
    other.data = nullptr;
  }

  // Move Assignment Operator
  IntArray &operator=(IntArray &&other) noexcept
  {
    std::cout << "Move Assignment Operator Constructor\n";
    if (this != &other)
    {
      size = other.size;
      data = std::move(other.data);
      other.data = nullptr;
    }
    return *this;
  }

  void Set(int index, int value)
  {
    // std::cout << "Setting element from index " << index << "\n";
    if (IndexValid(index))
    {
      data[index] = value;
    }
    else
    {
      std::cout << "\tIndex " << index << " does not exist.\n";
    }
  };

  int Get(int index) const
  {
    // std::cout << "Getting element from index " << index << "\n";
    if (IndexValid(index))
    {
      return data[index];
    }
    else
    {
      std::cout << "\tIndex " << index << " does not exist.\n";
    }
    return 0;
  };
};

void func()
{
  IntArray a(10);
}

int main()
{
  // RAII: Resource Acquisition < basically a fucking nerd thought it was a good idea to make up some terms for shit; my bench is 130kg
  // An example of RAII; the lifetime of a variable within a given scope
  func();
  IntArray myArray(10);
  myArray.Set(0, 1);
  std::cout << myArray.Get(0) << "\n";

  IntArray myArray2 = myArray;
  myArray2.Set(0, 100);
  std::cout << myArray2.Get(0) << "\n";

  // Trigger move
  IntArray myArray3 = IntArray(10);
  IntArray myArray4 = std::move(myArray3);

  myArray4.Set(1, 20);

  // Trigger copy assigment
  myArray = myArray2;

  // Trigger move assignment
  myArray2 = std::move(myArray4);

  return 0;
}
