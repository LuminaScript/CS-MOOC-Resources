## I.  Basic

### i. Assembly Basics: Register, operands, move

- **<u>Levels of Abstraction</u>**

  - **C code**

  - **Assembly programmer**  
    <img src="../../resources/csapp-3-01.png" alt="csapp-3-01" width="400" align="left"/>  
    <br clear="left"/>

  - **Computer designer**
    - caches, clock freq, layout, ...

- **<u>Definitions</u>**

  - **Architecture** (ISA, Instruction Set Architecture)
    - Machine Code: The byte-level programs that a processor executes
    - Assembly Code: A text representation of machine code
    - Example: Intel (x86, x86-64), ARM

  - **Microarchitecture**: Implementation of Architecture
    - Examples: cache sizes, core frequency


      

- **<u>Assembly Characteristics: Data Types</u>**

  - Integer data of 1, 2, 4, or 8 bytes
  - Floating point data of 4, 8, or 10 bytes
  - No aggregate types such as arrays or structures



- **<u>x86-64 Integer Registers</u>**  `%esp: lower 4 bytes`

  <img src="../../resources/csapp-3-02.png" alt="csapp-3-02" width="400" align="left"/>
  <br clear="left"/>


- **<u>Assembly Characteristics: Operations</u>**

  - **Transfer data** between memory and register

    - **Moving Data:  **

      - `movq Source, Dest`

        -  `q` = 8 bytes
        - <u>Operand 1#</u> - Immediate - Constant Integer Data - `$0x400, $-533` - `1, 2, or 4 bytes`
        - <u>Operand 2#</u> - Register - One of 16 Integer Register - `%rax`
        - <u>Operand 3#</u> - Memory -  `(%rax)`

      - `movq` operand combination (cannot do memory-memory transfer with a signle instruction)

        <img src="../../resources/csapp-3-03.png" alt="csapp-3-03" width="400" align="left"/>
        <br clear="left"/>

        

  - Perform **arithmetic function** on register or memory data

  - **Transfer control**: unconditional jumps, conditional & indirect branches



- **<u>Examples of Addressing Modes</u>**

  ```c
  void swap(long *xp /*%rdi*/, long *yp /*%rsi*/) { 
    long t0 = *xp;
    long t1 = *yp;
    *xp = t1;
    *yp = t0;
  }
  
  // Assembly:
  swap:
    movq (%rdi), %rax 
    movq (%rsi), %rdx 
    movq %rdx, (%rdi) 
    movq %rax, (%rsi) 
    ret
  ```



- **<u>Memory Addressing Modes</u>**

  - **Rules**:

    - Normal - `(R)` - `Mem[Reg[R]]`
    - D - Displacement 
    - Rb - Base Register (Any of 16 integer registers)
    - Ri - Index Register (Any, except for %rsp)
    - S - Scale - 1, 2, 4, or 8

  - **Forms**

    - `D(R)` - `Mem[Reg[R] + D]` - `movq 8 (%rbp), %rdx`
    - `D(Rb, Ri, S)` - `Mem[Reg[Rb] + S * Reg[Ri] + D]`
    - `(Rb, Ri)` - `Mem[Reg[Rb] + Reg[Ri]]`
    - `D(Rb, Ri)` - `Mem[Reg[Rb] + Reg[Ri] + D]`
    - `(Rb, Ri, S)` - `Mem[Reg[Rb] + S * Reg[Ri]]`

  - **Examples**:

    `%rdx | 0xf000` `%rcx | 0x0100`

    | Expression           | Address Computation | Address |
    | -------------------- | ------------------- | ------- |
    | **0x8 (%rdx)**       | 0xf000 + 0x8        | 0xf008  |
    | **(%rdx, %rcx)**     | 0xf000 + 0x0100     | 0xf100  |
    | **(%rdx, %rcx, 4)**  | 0xf000 + 4 * 0x0100 | 0xf400  |
    | **0x80 (, %rdx, 2)** | 2 * 0xf000 + 0x80   | 0x1e080 |


</br>

### ii. Arithmetic & Logical Operations


- **<u>Address Computation Instruction</u>**

  - `leaq Src, Dst`

    - Uses:

      - Compute addresses without a memory reference `p = &x[i]`

      - Compute arithmetic expressions of the form `x + k * y`  (k = 1, 2, 4, or 8)

        ```c
        long m12(long x) {
          return x * 12;
        }
        /* 
        - assembly - 
        leaq (%rdi, %rdi, 2), %rax # t = x + 2 * x
        salq $2, %rax # return t << 2
        */
        ```

  - **Arithmetic Operations**
  
    - **<u>Two Operands</u>**
      - `addq Src, Dest`: `Dest = Dest + Src`
      - `subq Src, Dest`: `Dest = Dest - Src`
      - `imulq Src, Dest`: `Dest = Dest * Src`
      - `salq Src, Dest`: `Dest = Dest << Src`
      - `sarq Src, Dest`: `Dest = Dest >> Src`
      - `shrq Src, Dest`: `Dest = Dest >> Src`
      - `xorq Src, Dest`: `Dest = Dest ^ Src`
      - `andq Src, Dest`: `Dest = Dest & Src`
      - `orq Src, Dest`: `Dest = Dest | Src`
  
    - **<u>One Operand</u>**
      - `incq Dest`: `Dest = Dest + 1`
      - `decq Dest`: `Dest = Dest - 1`
      - `negq Dest`: `Dest = -Dest`
    - `notq Dest`: `Dest = ~Dest`

  - **Arithmetic Expression Example**

    - High-Level Code

      ```c
      long arith(long x, long y, long z) {
          long t1 = x + y;
          long t2 = z + t1;
          long t3 = x + 4;
          long t4 = y * 48;
          long t5 = t3 + t4;
          long rval = t2 * t5;
          return rval;
      }
      ```

    - Assembly Code

      ```assembly
      arith:
          leaq (%rdi, %rsi), %rax  # t1 = x + y
          addq %rdx, %rax          # t2 = z + t1
          leaq (%rsi, %rsi, 2), %rcx  # t4 = y * 3 (part of y * 48)
          salq $4, %rdx            # t4 = y * 48
          leaq 4(%rdi, %rdx), %rcx # t5 = x + 4 + t4
          imulq %rcx, %rax         # rval = t2 * t5
          ret
      ```
    
</br>

### iii. C, assembly, machine code

- **Turning C into Object Code**

  - <u>Compiler</u>: C program  `.c`→ Asm program `.s`

    -  **`gcc -Og -S sum.c`** (on a shark machine)

  - <u>Assembler</u>: Asm program `.s` → Object program `.o`

    - `gcc` or `as`
    - Binary encoding of each instruction

  - <u>Linker</u>: Object program 1#  `.o`  + Object program 2#  `.o`  ... → Excutable program

    - `gcc` or `ld`
    - linkage between code of different files
    - static run-time libraries: Link static libraries `.a`

  - <u>Execution</u>:

    - dynamic run-time libraries

      

- **Machine Instruction Example**

  - **C Code**: `*dest = t;`
    - Store the value `t` where `dest` points to.
  - **Assembly**: `movq %rax, (%rbx)`
    - Move the value in the `rax` register into the memory location pointed to by the `rbx` register.
  - **Object Code**: `0x40059e: 48 89 03`
    - **48**: REX prefix for 64-bit operand.
    - **89**: Opcode for moving a 64-bit register to a memory location.
    - **03**: ModR/M byte indicating `rax` to memory pointed to by `rbx`.



- **Disassembling Object Code**

  - Disassebler:

    ```bash
    objdump –d sum
    ```

  - Within gdb debugger: 

    - Disassemble procedure

      ```bash
      gdb sum
      diassemble sumstore
      ```

    - Examine the 14 bytes starting at ` sumstore`

      ```bash
      x/14xb sumstore
      ```

      

    
