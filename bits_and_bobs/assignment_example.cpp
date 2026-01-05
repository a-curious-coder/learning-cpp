#include <iostream>

int main()
{
  int X = 2;
  int Y = 0;
  int Z = 0;

  Y = ++X;
  Z = X++;

  std::cout << "X: " << X << std::endl;
  std::cout << "Y: " << Y << std::endl;
  std::cout << "Z: " << Z << std::endl;
}
