#include <iostream>

class CPU {

  std::string instruction_set[5] = {"LOAD", "ADD", "STORE", "SUBTRACT", "HALT"};
  int AC = 0;
  int PC = 0;

public:
  bool running = true;

  // Constructor
  CPU(int memory[64]) {
    // While the cpu is running
    while (running) {
      int choice = memory[PC];
      //
      // Decode
      switch (choice) {
      case 0:
        std::cout << "LOAD" << std::endl;
        break;
      case 1:
        func();
        break;
      case 2:
        func2();
        break;
      case 3:
        func3();
        break;
      case 4:
        func4();
        break;
      default:
        std::cout << choice
                  << " is not a valid choice; choose from: 1, 2, 3 or 4."
                  << std::endl;
        break;
      }
      increment_program_counter();
    }
    std::cout << "CPU is dead - bye bye" << std::endl;
  }

private:
  void func() { std::cout << "ADD" << std::endl; }
  void func2() { std::cout << "STORE" << std::endl; }
  void func3() { std::cout << "SUBTRACT" << std::endl; }
  void func4() {
    std::cout << "EXIT" << std::endl;
    running = false;
  }
  void increment_program_counter() { PC += 2; }
};

int main() {
  // Initialised the cpu
  int memory[64] = {1, 1, 4, 2, 3, 6, 4, 3};
  CPU cpu(memory);

  return 0;
}
