Pętlik Language Implementation
Introduction
This project implements a programming language called Pętlik. The syntax of the language is defined by the following grammar, with Program as the starting symbol:

Program → InstructionSequence
InstructionSequence → ε | InstructionSequence Instruction
Instruction → Increment | Repeat
Increment → Variable
Repeat → '(' Variable InstructionSequence ')'
Variable → 'a' | .. | 'z'
The program consists only of characters enclosed in single quotes in the grammar. No other characters, including spaces or line breaks, are allowed in the source code.

The program has access to 26 variables, each representing a non-negative integer.

Execution Order
Instructions derived from the InstructionSequence symbol are executed in sequence, from first to last.

Increment instruction, represented as a variable, is equivalent to the following C instruction:

++variable;
Repeat instruction, in the form (variable...), is equivalent to the following C code:

while (variable > 0) { --variable; ... }
Virtual Machine Instructions
The implementation consists of an optimizing compiler that generates code for a virtual machine and an interpreter for executing that code. The virtual machine supports the following instructions:

INC Variable (increment): Increase the value of Variable by one.
ADD Variable0 Variable1 (add): Add the value of Variable1 to Variable0.
CLR Variable (clear): Set the value of Variable to zero.
JMP Address (jump): Jump to the instruction at the specified Address.
DJZ Variable Address (decrement or jump if zero): If Variable is zero, jump to the specified Address; otherwise, decrease Variable by one.
HLT (halt): Stop program execution.
Execution begins with the first instruction. Unless otherwise specified, execution proceeds to the next instruction in sequence.

Compiler Optimization
For a sequence of instructions, the compiler generates code in order from first to last. The generated code for the program ends with the HLT instruction.

For the Repeat instruction, if no other Repeat instruction is nested within, meaning the parentheses contain a sequence of variables Variable0, ..., VariableN for N >= 0, and none of the variables Variable1, ..., VariableN equals Variable0, the compiler generates optimized code as follows:

ADD Variable1 Variable0
...
ADD VariableN Variable0
CLR Variable0
If these optimization conditions are not met, standard code is generated.

Standard code for Increment instruction Variable:

INC Variable
Standard code for Repeat instruction (Variable...):

DJZ Variable End
...
JMP Start
where Start is the address of the first instruction in the sequence, and End is the address of the instruction immediately following the last instruction in the sequence.

Task
Write a program that implements the "Pętlik" language.

The program reads and executes commands to:

Print the value of a variable.
Execute a program written in the "Pętlik" language.
Before executing any commands, all variable values are initialized to 0.

Variables retain their values between command executions and are not reset before each program run.

Data Format
The input consists of a series of lines, each containing a single command.

Commands to print a variable’s value start with the = symbol, followed by the variable’s name.
Lines containing code in the Pętlik language represent commands to execute that code.
Output Format
The output of the program consists of the results of executing print commands for each variable. Each value is printed in decimal format, one per line, without leading zeros.

The value 0 is represented by the digit 0.
Positive values start with a non-zero digit.
