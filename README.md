# 8-Bit CPU Simulator in C

A low-level hardware simulation project focused on building a functional CPU architecture from scratch. This project simulates fundamental components including Logic Gates, Multiplexers, D-Type Flip-Flops, 8-bit Registers, and an Arithmetic Logic Unit (ALU).

## Project Structure

* **include/**: Header files (.h) containing struct definitions and function prototypes.
* **src/**: Source files (.c) containing the implementation of logic and hardware behavior.
* **Makefile**: Build script for easy compilation.

## Function Documentation

### ALU (Arithmetic Logic Unit)
* **Function**: `ALU_OUTPUT ALU(byte A, byte B, byte A_S)`
* **Receives**: 
    * `byte A`, `byte B`: Two 8-bit inputs.
    * `byte A_S`: Control signal (Add/Subtract).
* **Returns**: `ALU_OUTPUT` struct containing the 8-bit result (`RES`) and hardware flags (`Z`, `N`, `C`, `V`).
* **Description**: Simulates a bit-by-bit ripple carry adder/subtractor. It calculates the result and updates status flags for Zero, Negative, Carry, and Overflow.

### D-Type Flip-Flop (DFF)
* **Function**: `void update_DFF(DFF *dff, uint8_t d, uint8_t clk)`
* **Receives**: 
    * `DFF *dff`: Pointer to the DFF structure to be updated.
    * `uint8_t d`: The data input bit (0 or 1).
    * `uint8_t clk`: The current clock signal (0 or 1).
* **Returns**: `void`
* **Description**: Updates the internal state of a flip-flop. It captures the input `d` only on the rising edge of the clock signal.

### Register (8-bit)
* **Function**: `void update_register(register8 reg, int8_t data, int clock)`
* **Receives**: 
    * `register8 reg`: The array of 8 DFFs representing the register.
    * `int8_t data`: The 8-bit value to be stored.
    * `int clock`: The current clock signal.
* **Returns**: `void`
* **Description**: Iterates through each bit of the input data and updates the corresponding DFF within the register.

### Byte Retrieval
* **Function**: `byte get_full_byte(register8 reg)`
* **Receives**: `register8 reg` (the array of 8 DFFs).
* **Returns**: `byte` (int8_t).
* **Description**: Reads the `q` state of all 8 DFFs and reconstructs them into a single 8-bit integer (byte).

### Multiplexer (MUX)
* **Function**: `int8_t MUX(int a, int b, int s)`
* **Receives**: Inputs `a`, `b` and a selector `s`.
* **Returns**: `int8_t` (the value of `a` if `s=0`, or `b` if `s=1`).
* **Description**: Fundamental component used for signal routing and state selection.

## Build and Run

To compile the project, use the provided Makefile:

```bash
make
./CS01
