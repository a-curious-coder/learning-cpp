#include <iostream>

std::string instruction_set[5] = {"LOAD", "ADD", "STORE", "SUB", "HALT"};
enum opcode { load = 0, add = 1, store = 2, sub = 3, halt = 4 };

class CPU {
  // Accumulator (sticky note - holds previous value)
  int AC = 0;
  // Program Counter (increments to ensure free space of memory?)
  int PC = 0;

public:
  bool running = true;

  // Constructor
  CPU(int memory[32]) {
    std::cout << "PC\tISA\tVAL\tAC" << std::endl;
    // While cpu is running
    while (running) {
      int instruction = memory[PC];
      PC++;
      int value = memory[PC];
      PC++;
      if (PC >= 32)
        running = false;
      // Decode
      if (instruction == 0 && value == 0)
        continue;

      std::string instruction_string = get_instruction_string(instruction);
      std::cout << "-------------------------------" << std::endl;
      std::cout << PC << "\t" << instruction_string << "\t" << value << "\t"
                << AC << std::endl;
      std::cout << "\nExecute " << instruction_string << " given value "
                << value << "\n"
                << std::endl;
      switch (instruction) {
      case load:
        AC = memory[value];
        break;
      case add:
        AC = AC + value;
        break;
      case store:
        memory[value] = AC;
        break;
      case sub:
        AC = AC - value;
        break;
      case halt:
        break;
      }
      AC = value;
      std::cout << PC << "\t" << instruction_string << "\t" << value << "\t"
                << AC << std::endl;
    }
    std::cout << "CPU is dead - bye bye" << std::endl;
  }

private:
  std::string get_instruction_string(int instruction) {
    return instruction_set[instruction];
  }
};

int main() {

  int memory[64] = {load, 1, sub, 2, store, 6, load, 3};
  CPU cpu(memory);

  return 0;
}
