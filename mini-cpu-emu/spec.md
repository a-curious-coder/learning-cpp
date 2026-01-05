# CPU Emulator
Simple linear memory model with a general-purpose register (Accumulator)

Memory: array of 16 integers
## Registers
PC - Program Counter
> points to next instruction 

AC - Accumulator
> stores result of last operation

Each instruction consists of an **Opcode** (the action) and the **Operand** (the data or address)

## ISA - Instruction Set 
---
LOAD - load value from memory address into AC
ADD - Add value from memory address into AC
STORE - Store value from AC into memory address
SUB - Subtract value at memory address from AC
HALT - Stop execution

## Implementation
---
Utilise a while loop representing Fetch-Decode-Execute cycle
1. Fetch: instruction from memory at the position represented by the program counter
2. Decode: determine if the value is a 1,2,3,4 or 0
3. Execute: perform the math or memory move corresponding to the decoded value
4. Increment: move the program counter by 2 (1 representing opcode and another 1 representing operand)
