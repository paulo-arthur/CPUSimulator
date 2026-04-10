# CPUSimulator

A low-level hardware simulation project developed in C. The goal is to build a functional CPU model starting from basic logic gates and arithmetic units, moving towards a complete instruction cycle.

## Current Status: ALU (Arithmetic Logic Unit)

The project currently features a fully implemented ALU capable of performing fundamental operations. The focus was on ensuring mathematical precision and correct flag handling.

* **Logic Operations:** AND, OR, XOR, NOT.
* **Arithmetic Operations:** Addition and Subtraction.
* **Flag System:**
    * **Zero (Z):** Set when the result is zero.
    * **Negative (N):** Set if the result is negative (MSB is 1).
    * **Carry (C):** Set on unsigned overflow.
    * **Overflow (V):** Set on signed overflow, detecting inconsistencies in arithmetic results.

## Ongoing Development: Memory & State

The current phase focuses on the implementation of **Latches and Registers**. 

The main challenge is simulating the feedback loops required for state retention. I am evaluating the implementation of:
* **SR and D-Type Latches** to form the basis of the memory hierarchy.
* **Clock synchronization** logic to manage the transition from combinational to sequential logic.
* **Program Counter (PC) and Accumulator** initialization.

## How to Run

1.  Compile the source:
    ```bash
    gcc -o main main.c alu.c
    ```
2.  Execute:
    ```bash
    ./main
    ```
