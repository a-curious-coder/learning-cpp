#include <iostream>

class CPU {

  std::string instruction_set[5] = {"LOAD", "ADD", "STORE", "SUBTRACT", "HALT"};
  // Accumulator (sticky note - holds previous value)
  int AC = 0;
  // Program Counter (increments to ensure free space of memory?)
  int PC = 0;

public:
  bool running = true;

  // Constructor
  CPU(int memory[64]) {
    // While cpu is running
    while (running) {
      int instruction = memory[PC];
      std::string instruction_string = return_instruction_string(instruction);

      int value = memory[PC + 1];
      increment_program_counter();
      // Decode
      switch (instruction) {
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
        std::cout << "Yurt" << std::endl;
        break;
      }
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
  std::string return_instruction_string(int instruction) {
    return instruction_set[instruction];
  }
  void increment_program_counter() { PC += 2; }
};

int main() {
  enum opcode { load = 0, add = 1, store = 2, sub = 3, halt = 4 };

  int memory[64] = {load, 1, sub, 2, store, 6, load, 3};
  CPU cpu(memory);

  return 0;
}
