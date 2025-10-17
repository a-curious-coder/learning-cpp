#include <iostream>

constexpr int factorial(int a)
{
  return a == 1 ? a : a * factorial(a-1);
};

int main() {
  std::cout << factorial(3) << "\n";
  std::cout << factorial(6) << "\n";
  std::cout << factorial(9) << "\n";
  return 0;
}
