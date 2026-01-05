#include <iostream>
#include <bitset>

int bit_length(int num) {
  int num_bytes = sizeof(num);
  int num_bits = num_bytes * 8;
  std::cout << "bytes: " << num_bytes << '\n';
  std::cout << "bits: " << num_bits << '\n';

  int bit_count = 0;
  for(int i = 0; i < num_bits; i++)
  {
    if(num == 0) {
      break;
    }
    std::bitset<32> x(num);
    std::cout << "binary: " << x << '\n';
    std::cout << num << ", " << bit_count << '\n';
    bit_count += ((num & (1 << i)) != 0);
  }
  return bit_count;
};

int main() {
  std::cout << bit_length(257) << '\n';
  return 0;
}
