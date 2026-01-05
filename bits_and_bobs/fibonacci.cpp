#include <iostream>

constexpr int fib(int index) {
  if(index == 0 || index == 1)
  {
    return index;
  };
  return fib(index-2) + fib(index-1);
}

int main() {
  std::cout << fib(10) << '\n';
  return 0;
}
