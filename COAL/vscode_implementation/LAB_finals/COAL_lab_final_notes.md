---
# Auto-filled tags
title: COAL_lab_final_notes
date: November 27, 2025
datenum: 20251127
day: Thursday
time: 2025-11-27T09:30:42+05:00
UNIX timestamp: 1764217842
from: FAST
field: BSAI
semester: 3

# User-filled tags
aliases: []
tags: []
type:
  - notes
  - study
  - university
  - classwork
note-level: 1
author: [Rafay Siddiqui | 24K-0009]
abstract: this is an abstract
description:
# course auto fill
course: EL2003-COAL

class:
cssclasses:
  - center-titles
  - image-borders

# Note: Pandoc LaTeX-compliant tags include 'title', 'abstract', 'author', and 'date'.
---

<span style="font-style:italic; font-weight:bold; color:rgb(255, 0, 0)">Topic:</span> **COAL_lab_final_notes**

****<span style="font-weight:bold; font-weight:bold; color:rgb(255, 192, 0)">File Creation Date:</span>** Nov 27, 2025 // Thursday //  09:30 

<font color="#548dd4">Last Modified:</font>  Nov 27, 2025 // Thursday //  09:30

**<span style="font-weight:bold; color:rgb(146, 208, 80)">Course:</span>** 
**<span style="font-weight:bold; font-weight:bold; color:rgb(0, 176, 240)">Class:</span>** 

---

# FAQs
  
- `offset var` vs `[eax]`
  - offset returns refernce from memory
  - while `[eax]` is indirect addressing
    - `eax` stores some address in memory
    - `[eax]` returns the value from that address
- use of `esi`
- what is stack frame
  - a temporary stack made for one procedure call
  - the stack contains

```
| Higher Memory (Old stack data) |
---------------------------------
| [EBP + 12]  Parameter 2        |
| [EBP + 8]   Parameter 1        |
| [EBP + 4]   Return Address     |  <-- where RET will jump back
| [EBP + 0]   Old EBP (saved)    |  <-- we store caller's EBP here
---------------------------------
| Local variables (if any)       |  <-- we may allocate space here
---------------------------------
| Lower Memory (grows downward)  |
```

- here:
```
push ebp      ; Save caller’s EBP (old base pointer)
mov ebp, esp  ; Make EBP point to this spot → start of this function's frame

```
- ebp gets saved to global stack, 

- what is `ret`?
- it pops val from stack into `EIP`
- which causes `EIP` to jmp to the procedure
# LAB 4 - Working with operators

## Operand Types
- *reg8* 8-bit general-purpose register: AH, AL, BH, BL, CH, CL, DH, DL
- *reg16* 16-bit general-purpose register: AX, BX, CX, DX, SI, DI, SP, BP
- *reg32* 32-bit general-purpose register: EAX, EBX, ECX, EDX, ESI, EDI, ESP, EBP
- *sreg* 16-bit segment register: CS, DS, SS, ES, FS, GS
- *imm8* 8-bit immediate byte value
- *imm16* 16-bit immediate word value
- *imm32* 32-bit immediate doubleword value
- *reg/mem8* 8-bit operand (register or memory byte)
- *reg/mem16* 16-bit operand (register or memory word)
- *reg/mem32* 32-bit operand (register or memory doubleword)

## MOV Instruction
- **Function:** Moves data from source operand to destination operand
- **Syntax:** `MOV destination, source`
- **Rules:**
  - Both operands must be the **same size**
  - Both operands **cannot** be memory operands
  - **CS, EIP, and IP** cannot be destination operands
  - Immediate value **cannot** be moved to a segment register
- **Data Formats (Equivalent examples):**
  - Decimal: `MOV bx, 65d`
  - Hex: `MOV bx, 41h`
  - Binary: `MOV bx, 01000001b`
  - ASCII: `MOV bx, 'A'`
- **Compatibility:**

```
MOV ax, 2 ✔
MOV ax, var ✔
MOV var, ax ✔
MOV 2, ax ❌
MOV var1, var2 ❌
MOV 5, var ❌
```
- **Overlapping Values:**
  - Moving to *AL* changes EAX bits 0-7
  - Moving to *AX* changes EAX bits 0-15
  - Moving to *EAX* changes EAX bits 0-31

## Extended Move Instructions

- *MOVZX* moves and **zero-extends** value to 16/32 bits; used with *unsigned* integers
- *MOVSX* moves and **sign-extends** value to 16/32 bits; used with *signed* integers
- **Syntax:** `MOVZX/MOVSX reg32, reg/mem8` (and variations)

## Arithmetic Instructions
- *INC* takes operand and *adds* 1 to it
- *DEC* takes operand and *subtracts* 1 from it
- *ADD* *adds* source to destination (sum stored in dest)
- *SUB* *subtracts* source from destination (result stored in dest)
- *NEG* *reverses* sign of number (converts to two’s complement)
- **XCHG** *exchanges* contents of two operands (***No immediate operands allowed***)

## Symbolic Constants
- **Equal-Sign (=) Directive:**
    - Associates symbol with integer expression
    - *Can* be redefined in program
    - Syntax: `name = expression`
- **EQU Directive:**
    - Associates symbol with integer or text (preprocessor step)
    - *Cannot* be redefined
    - Syntax: `name EQU expression` / `name EQU <text>`
- **Difference Example:**
    - `matrix1 EQU 10 * 10` evaluates to integer **100**
    - `matrix2 EQU <10 * 10>` copies text **10 \* 10**

## Complex Expression Logic
- **Equation:** `Rval = -Xval + (Yval - Zval)`
- **Step 1:** Negate Xval (`MOV eax, xval` -> `NEG eax`)
- **Step 2:** Calculate Y - Z (`MOV ebx, Yval` -> `SUB ebx, Zval`)
- **Step 3:** Add terms (`ADD eax, ebx` -> `MOV Rval, eax`)


# LAB 5 - Data related Operator and Directives Addressing

## Arithmetic Effects on Flag Registers

 - **Z-Zero Flag (ZF):** Set when result is zero (*ZF=1* if result is *0*, *ZF=0* if result *non-zero*)
     - `FFFFh + 1h = 10000h` (Result is 0 in 16-bit register)
 - **C-Carry Flag (CF):** Set when unsigned value is out of range (carry/borrow at MSB)
     - *INC* and *DEC* instructions do *not* set the *Carry Flag*
     - *ADD* sets CF if *carry* occurs (`0Fh + F1h = 100h`)
     - *SUB* sets CF if *borrow* occurs (`12AEh - 12AFh`)
 - **S-Sign Flag (SF):** Set if result is negative (MSB is 1)
 - **AC-Auxiliary Carry Flag:** Set if carry/borrow occurs at lowest nibble (bit 3)
     - `Add al, 1` (Where AL was 0Fh, carry moves from bit 3 to 4)
 - **P-Parity Flag (PF):** Set if *lower 8 bits* contain *even* number of 1s
     - *26 (11010)* has *odd* 1s -\> *PF=0*
     - *102 (1100110)* has *even* 1s -\> *PF=1*
 - **O-Overflow Flag (OF):** Set if signed result is out of range
     - `+128` is out of signed 8-bit range

## Direct-Offset Operands

- **Function:** Adds displacement to variable name to access memory
- *BYTE* array jump is *+1*
- *WORD* array jump is *+2*




```assembly
mov al,arrayB       ; AL = 10h
mov al,[arrayB+1]   ; AL = 20h
mov ax,arrayW       ; AX = 100h
mov ax,[arrayW+2]   ; AX = 200h
```

## Data Related Operators

### **`OFFSET` Operator**

-  **Function:** Returns distance in bytes from segment beginning to label
-  *bVal* offset is *00404000*
-  *wVal* offset is *00404001* (1 byte later)
-  *dVal* offset is *00404003* (2 bytes later)


```assembly
mov esi, OFFSET bval
```

### **`PTR` Operator**

  * **Function:** Overrides operand's default size
  * **Constraint:** Must be same size as destination normally
  * **Syntax:** `type PTR expression`
```assembly
mov eax, DWORD PTR wordList ; Moves 2 words into 32-bit EAX
```

### **`TYPE` Operator**

  * **Function:** Returns size of single element in bytes
  * *BYTE* returns *1*
  * *WORD* returns *2*
  * *DWORD* returns *4*
  * *QWORD* returns *8*
```assembly
mov ax, type var1 ; AX = 1
```

### **`LENGTHOF` Operator**

  * **Function:** Counts elements in array based on declaration line
  * **Rule:** Counts values on the *same line* as label only
      * *Comma-separated lines:* counted as *one* array
      * *Separate lines:* counted as *separate* declarations

### **`SIZEOF` Operator**

  * **Function:** Returns total byte size (`LENGTHOF * TYPE`)
```assembly
mov eax,SIZEOF intArray ; 32 elements * 2 bytes = 64
```

## Indirect Operands

-  **Function:** Uses 32-bit register as pointer (address holder)
-  **Syntax:** `[Register]`

```assembly
mov esi, OFFSET byteVal
mov al, [esi]       ; Dereferences address in ESI
```
  * **Modification:** Requires `PTR` when size is ambiguous
      * `inc [esi]` ❌ (Error: size unknown)
      * `inc BYTE PTR [esi]` ✔
      * `inc WORD PTR [esi]` ✔

## Array Traversal (Indirect)

  * **Logic:** Increment pointer address based on data type size
  * *Byte* array: add *1* to ESI
  * *Word* array: add *2* to ESI
  * *Dword* array: add *4* to ESI
    ```assembly
    add esi, 2 ; Move to next WORD
    add esi, 4 ; Move to next DWORD
    ```

## Indexed Operands

  * **Function:** Adds constant to register for effective address
  * **Syntax:** `constant[reg]` or `[constant + reg]`
    ```assembly
    mov al, arrayB[esi]   ; Base + Index
    mov al, [arrayB + esi]
    ```

## Scale Factors

  * **Function:** Automates offset calculation using `TYPE`
  * **Syntax:** `[reg * TYPE var]`

```assembly
mov ax, arrayW[esi * TYPE arrayW]
```


# LAB 6 - intro to loops and Irvine instructions

## CMP (Compare) Instruction
* **Purpose:** Compares two operands by performing internal subtraction (*Destination – Source*).
* **Syntax:** `CMP Destination, Source`
* **Behavior:** Discards result; updates **CPU flags** (Zero, Sign, Carry, Overflow) to determine program flow.
* **Usage:** Checks equality, greater than, or less than conditions for conditional jumps.
* **Ignored Flags:** *Auxiliary Carry Flag (AF)* and *Parity Flag (PF)* are **not relevant** in comparisons.



## CMP Logic & Flag Status
* **Case 1:** *`Dest > Src`* $\rightarrow$ Result is *+ve* $\rightarrow$ **Flags:** *`CF=0`, `ZF=0`, `SF=0`*
* **Case 2:** *`Dest = Src`* $\rightarrow$ Result is *0* $\rightarrow$ **Flags:** *`CF=0`, **`ZF=1`**, `SF=0`*
* **Case 3:** *`Dest < Src`* $\rightarrow$ Result is *-ve* $\rightarrow$ **Flags:** *`CF=1`, `ZF=0`, **`SF=1`***

## Jump Instructions
* **Purpose:** Modifies Instruction Pointer (IP/EIP) to alter execution flow.
* **Unconditional Jump:**
    * **Syntax:** `JMP destination`
    * **Action:** Always transfers control to label; ignores all conditions.
* **Conditional Jump:**
    * **Syntax:** `Jcond destination` (e.g., JE, JNE, JC)
    * **Action:** Transfers control **only** if specific flags are set (True); otherwise continues sequentially.
    * **Process:** 1. Test condition (CMP/TEST) → 2. Jump based on flags.



## LOOP Instruction
* **Purpose:** Executes block of instructions repeatedly.
* **Syntax:** `LOOP destination`
* **Counter:** Uses *CX* (16-bit) or *ECX* (32-bit).
* **Logic:**
    1.  Decrements *CX/ECX* by 1.
    2.  If *CX/ECX ≠ 0*, jumps to destination.
    3.  If *CX/ECX = 0*, exits loop.

## Irvine Library Procedures (Input/Output/Control)
* **Clrscr:** Clears console and resets cursor to top-left corner.
* **Crlf:** Prints newline (carriage return + line feed).
* **WriteBin:** Prints *EAX* as unsigned 32-bit binary.
* **WriteChar:** Prints single character stored in *AL*.
* **WriteDec:** Prints *EAX* as unsigned 32-bit decimal.
* **WriteHex:** Prints *EAX* as 32-bit hexadecimal.
* **WriteInt:** Prints *EAX* as signed 32-bit decimal.
* **WriteString:** Prints null-terminated string pointed to by *EDX*.
* **ReadChar:** Waits for keypress; returns character in *AL*.
* **ReadDec:** Reads unsigned decimal from keyboard into *EAX*.
* **ReadHex:** Reads hexadecimal from keyboard into *EAX*.
* **ReadInt:** Reads signed decimal from keyboard into *EAX*.
* **ReadString:** Reads string from keyboard (uses *EDX* for offset, *ECX* for max size).
* **Delay:** Pauses execution for *EAX* milliseconds.
* **Randomize:** Seeds random number generator.
* **DumpRegs:** Displays all major registers (EAX, EBX, EIP, EFLAGS, etc.).
* **DumpMem:** Displays memory block (*ESI* = Start, *ECX* = Length, *EBX* = Type).
* **GetDateTime:** Returns system date and time.
* **GetMaxXY:** Returns buffer size (*DX* = Columns, *AX* = Rows).
* **GetTextColor:** Returns current color (*AL* = Foreground, *AH* = Background).
* **Gotoxy:** Moves cursor to specific location (*DH* = Row, *DL* = Column).
* **MsgBox:** Displays message box (*EDX* = String, *EBX* = Title).
* **MsgBoxAsk:** Displays Yes/No box (*EDX* = String, *EBX* = Title); returns *EAX=6* (Yes) or *EAX=7* (No).
* **SetTextColor:** Sets console colors (*EAX* = Foreground + (Background * 16)).
* **WaitMsg:** Displays message and waits for Enter key.

# LAB 7 - conditional Jumps



## ***Boolean and Comparison Instructions***

### `AND` Instruction
Syntax: 
```
AND reg, reg
AND reg, mem
AND reg, imm
AND mem, reg
AND mem, imm

```

- `AND` *clears* the `CF` and `OF`. 
- It modifies the `SF` `ZF` and `PF` in a way that is consistent with the value assigned to the destination operand

>[!note] The All other instructions use the same operand combinations and sizes as the AND instruction.

### `OR` Instruction

```
mov al,11100011b
or  al,00000100b ; result in AL = 11100111
```

- The `OR` always *clears* ... (same as `AND`)

### `XOR` Instruction
- same as `AND` `OR`

###  `NOT` Instruction
The NOT instruction toggles (inverts) all bits in an operand. [[1's complement.]]

Syntax: 
```
NOT reg
NOT mem
```


```
mov al, 11110000b
xor al ; al = 00001111b
```

### `TEST` Instruction

- performs an implied `AND` operation and sets the `SF`, `ZF`, and `PF` based on the value assigned to the `dest` 

> [!note] only difference is that `TEST` does not modify the destination operand.

#### Testing Multiple Bits
- `TEST` can check several bits at once. 
- Suppose we want to know whether bit 0 or bit 3 is set in the AL register. 
- We can use the following instruction to find this out:

```

EXAMPLE
.code
mov  al, 10101110b ; Clear only bit 3
and  al, 11110110b ; AL = 10100110

mov  al, 11100011b ; set bit 2
or   al, 00000100b ; AL = 11100111

mov  al, 10110101b ; 5 bits means odd parity
xor  al, 0         ;PF=0(PO)

mov  al, 10100101b ; 4 bits means even parity
xor  al, 0         ;PF=1(PE)


mov  al, 11110000b
not  al            ; AL = 00001111b

mov  al, 00100101b
test al, 00001001b ;ZF=0

mov  al, 00100101b
test al, 00001000b ;ZF=1

call DumpRegs
exit

```

### CMP Instruction
- `CMP` performs an implied subtraction of  `SRC`  `destination` for comparison. 
- Neither operand is modified.

Syntax:

```
CMP dest, src
```

- Flags: `CMP` changes the `OF` `SF` `ZF` `CF` `AF` and `PF` according to `dest`
- When two *unsigned operands* are compared:
```
DEST < SRC ; ZF=0 CF=1
DEST > SRC ; ZF=0 CF=0
DEST = SRC ; ZF=1 CF=0
```

- When two *signed operands* are compared:
```
Destination < source SF!=OF
Destination > source SF =OF
Destination = source ZF =1
```

Examples: Let’s look at three code fragments showing how flags are affected by the CMP instruction.
```
.code
mov ax, 5

cmp ax, 10 ; ZF = 0 and CF = 1

mov ax, 1000
cmp ax, 1000 ;ZF=1 and CF =0


mov si, 106
cmp si, 0 ;ZF=0 and CF=0
```

##  *Conditional Jumps*
- CMP, AND, or SUB *modifies* the flags.
- `JMP` tests the flags and causes a branch to a new address.


### `Jcond` Instruction
branches to a destination label when a status flag condition is true.

```
Jcond Dest
```

The conditional jump instructions can be divided into four groups:

- jump if...

***Jumps based on Flag values***

| mnemonic | Destination | Flags |
| -------- | ----------- | ----- |
| `JZ`     | zero        | ZF=1  |
| `JNZ`    | not zero    | ZF=0  |
| `JC`     | carry       | CF=1  |
| `JNC`    |             | CF=0  |
| `JO`     | overflow    | OF=1  |
| `JNO`    |             | OF=0  |
| `JS`     | signed      | SF=1  |
| `JNS`    |             | SF=0  |
| `JP`     | parity      | PF=1  |
| `JNP`    |             | PF=0  |

***Jumps based on Equality***

| mnemonic | description |
| -------- | ----------- |
| JE       | equal       |
| JNE      | not equal   |
| JCXZ     | cx = 0      |
| JECXZ    | ecx = 0     |

***Jumps based on unsigned comparisons***

| mnemonic | description    |
| -------- | -------------- |
| JA       | above          |
| JNA      |                |
| JAE      | above or equal |
| JNAE     |                |
| JB       | below          |
| JNB      |                |
| JBE      | below or equal |
| JNBE     |                |

***Jumps based on signed comparisons***

| mnemonic | description |
| -------- | ----------- |
| JG       | greater     |
| JNG      |             |
| JGE      | g equal     |
| JNGE     |             |
| JL       | leser       |
| JNL      |             |
| JLE      | l eq        |
| JNLE     |             |

```EXAMPLE
; This program compares and finds larger of the two integers
INCLUDE Irvine32.inc
.data
var1 DWORD 500
var2 DWORD 125
larger DWORD ?
.code
main PROC
	mov eax, var1
	mov larger, eax
	mov ebx, var2
	cmp eax, ebx
	jae L1
	mov larger, ebx
	L1:
	exit
main ENDP
END main
```

```EXAMPLE
; This program compares and finds smallest of the three integers
.data

.code
var1 DWORD 50
var2 DWORD 25
var3 DWORD 103
msg BYTE "The smallest integer is: ", 0
mov eax, var1
cmp eax, var2
jbe L1
mov eax, var2
L1:
cmp eax, var3
jbe L2
mov eax, var3
L2:
mov edx, OFFSET
msg call WriteString
call crlf
call WriteDec
call crlf
exit
```

### Conditional Loop Instructions
- `LOOPZ` (loop is `ZF=1`)

```
LOOPZ dest
```
- The `LOOPE` (loop if equal) 

- `LOOPNZ` and `LOOPNE` Instructions


```
; The following take input from user until user press 0
.code
mov    ecx,5
L1:
	CALL   readInt
	cmp    eax, 0
	LOOPNZ L1
	call DumpRegs
  ```



### Conditional Structures

#### Block-Structured `IFs`
An IF structure implies that a boolean expression is followed by two lists of
statements; one per-formed when the expression is true, and another performed when
the expression is false.

```
if(expr)
	s1
else
	s2
```

If structure: In High level Vs Assembly Language

```
if(o1==o2){
	x=1;
	y=2;
}
```

```
mov eax, o1
cmp eax, o2 ;(o1==o2)?
jne l1      ; no: skip to l1

mov x, 1    ; yes: assign x and y
mov y, 2

l1:

```

Compound Expression with AND

```
if (a>b) && (b>c)
	x=1;
```

```
	cmp al,b1
	ja l1
	jmp next
l1:
	cmp b1,c1
ja l2
	jmp next
l2:
	mov x, 1
next:
```

Compound Expression with OR


```
if (a>b) || (b>c)
	x=1;
```

```
cmp al,bl
ja l1
cmp bl, cl
jbe next
l1:
mov x,1
next:
```

While Loops

```
while(a<b)
	a++
```

```
TOP:
cmp eax, ebx 
jae NEXT
inc eax
jmp TOP
NEXT:
```


# LAB 8: Stack Operations and Procedures

## Runtime Stack Overview
* **Structure:** LIFO (Last-In, First-Out) data structure.
* **Hardware Support:** Directly supported by CPU; essential for procedure calls/returns.
* **Key Registers:**
    * **SS (Stack Segment):** Holds the segment selector.
    * **ESP (Stack Pointer):** Points to the last value added (top of stack).

![[Drawing 2025-11-29 15.28.53_stack in memory.excalidraw.png|300]]

## PUSH Operation
* **Function:** *Adds* a value to the top of the stack.
* **Mechanism (32-bit):**
    1.  ***Decrements*** **ESP** by 4.
    2.  Copies operand value into location pointed to by **ESP**.
* **Syntax:**
    * `PUSH r/m16`
    * `PUSH r/m32`
    * `PUSH imm32`


## POP Operation
* **Function:** *Removes* a value from the top of the stack.
* **Mechanism:**
    1.  Copies value at **[ESP]** to destination (register or variable).
    2.  ***Increments*** **ESP** by element size (e.g., 4 for 32-bit).
* **Syntax:**
    * `POP r/m16`
    * `POP r/m32`


## Flag Register Operations
* **Restriction:** `MOV` instruction cannot copy flag registers directly.
* **PUSHFD:** Pushes 32-bit **EFLAGS** register onto the stack.
* **POPFD:** Pops the top of the stack into the **EFLAGS** register.

## Application Examples
* **Nested Loops:** Stack preserves outer loop counters while inner loops execute.
* **Arithmetic (Calculator):**
    * Push operands -> Pop & Calculate -> Push Result -> Pop & Display.
* **Undo/Redo (LIFO Logic):**
    * Push version history (latest last).
    * Pop into new array (results in reverse order/rollback).
* **Data Processing:**
    * Compute product of pushed integers.
    * Determine largest number using stack storage.

## Procedures (Subroutines)
* **Purpose:** Modular blocks of code performing well-defined jobs.
* **Directives:**
    * `PROC`: Declares start of procedure (e.g., `Sample PROC`).
    * `ENDP`: Declares end of procedure (e.g., `Sample ENDP`).
* **Constraint:** Must end with `RET` instruction (except startup procedure).

## Control Flow Instructions
* **CALL Instruction:**
    * **Usage:** `CALL ProcedureName`
    * **Step 1:** Pushes address of *next* instruction (return address) to stack.
    * **Step 2:** Updates Instruction Pointer (IP) to address of first instruction in procedure.

* **RET Instruction:**
    * **Usage:** Used at end of procedure.
    * **Step 1:** Pops return address from stack into Instruction Pointer (IP).
    * **Step 2:** Resumes execution in caller program.

## Nested Procedures
* **Definition:** A procedure calls another procedure before returning.
* **Stack Behavior:** Multiple return addresses stack up; resolved in LIFO order upon `RET`.

## PROBLEM: reverse a string

```
INCLUDE Irvine32.inc

.data
    prompt  BYTE "Enter a string to reverse: ",0
    buffer  BYTE 50 DUP(?)
    nameSize DWORD ?

.code
main PROC
    ; 1. Get User Input
    mov edx, OFFSET prompt
    call WriteString
    mov edx, OFFSET buffer
    mov ecx, SIZEOF buffer
    call ReadString
    mov nameSize, eax        ; Save number of characters typed

    ; 2. Push to Stack (LIFO Entry)
    mov ecx, nameSize        ; Loop counter = string length
    mov esi, 0               ; Index = 0

PushLoop:
    movzx eax, buffer[esi]   ; Move byte to EAX (zero-extended)
    push eax                 ; Push character to Top of Stack
    inc esi                  ; Move to next character
    loop PushLoop

    ; 3. Pop from Stack (LIFO Exit)
    mov ecx, nameSize        ; Reset loop counter

PopLoop:
    pop eax                  ; Pop Top of Stack into EAX
    call WriteChar           ; Print character
    loop PopLoop

    call Crlf
    exit
main ENDP
END main
```


# LAB 9: Integer Arithmetic (Shift, Rotate, Mul, Div)

## Shift Instructions

  * Moves bits *right* or *left*, shifting into *Carry Flag (CF)*.
### **`SHL` (Shift Left)** 
  * Shifts *left*, fills *LSB* with *0*, moves *MSB* to *CF*. (Multiplies by $2^n$).
```assembly
SHL destination, count
mov bl, 8Fh ; BL = 10001111b
shl bl, 1   ; BL = 00011110b, CF = 1
```
### **`SHR` (Shift Right)** 
  * Shifts *right*, fills *MSB* with *0*, moves *LSB* to *CF*. (Divides *unsigned* by $2^n$).
```assembly
mov al, 0D0h ; AL = 11010000b
shr al, 1    ; AL = 01101000b, CF = 0
```
### **`SAL` (Shift Arithmetic Left)** 
  * Identical operation to `SHL`.
### **`SAR` (Shift Arithmetic Right)** 
  * Shifts *right*, *duplicates* sign bit (MSB), moves *LSB* to *CF*. (Divides *signed* by $2^n$).
```assembly
mov al, 0F0h ; AL = 11110000b (-16)
sar al, 1    ; AL = 11111000b (-8), CF = 0
```

## Rotate Instructions

  * Bits rotated out one end are put back into the other end.
### **`ROL` (Rotate Left)** 
  * Shifts *left*, *MSB* copies to both *CF* and *LSB*.
```assembly
mov al, 40h ; AL = 01000000b
rol al, 1   ; AL = 10000000b, CF = 0
```
### **`ROR` (Rotate Right)** 
  * Shifts *right*, *LSB* copies to both *CF* and *MSB*.
```assembly
mov al, 01h ; AL = 00000001b
ror al, 1   ; AL = 10000000b, CF = 1
```
### **`RCL` (Rotate Carry Left)** 
  * Shifts *left*, *CF* moves to *LSB*, *MSB* moves to *CF*.
```assembly
clc         ; CF = 0
mov bl, 88h ; BL = 10001000b
rcl bl, 1   ; BL = 00010000b, CF = 1
```
### **`RCR` (Rotate Carry Right)** 
  * Shifts *right*, *CF* moves to *MSB*, *LSB* moves to *CF*.

```assembly
stc         ; CF = 1
mov ah, 10h ; AH = 00010000b
rcr ah, 1   ; AH = 10001000b, CF = 0
```


## Double Precision Shifts

  * Shifts destination while filling vacant bits from a source operand.
### SHLD (Shift Left Double)
  * Shifts *dest* left, fills *LSB* gaps from *source MSBs*.
    ```assembly
    SHLD dest, src, count
    shld a, ax, 4 ; a shifts left, bits from ax fill in
    ```
### SHRD (... Right ...)
  * Shifts *dest* right, fills *MSB* gaps from *source LSBs*.
    ```assembly
    shrd ax, dx, 4 ; ax shifts right, bits from dx fill in
    ```


## Multiplication

### `MUL` (unsigned multiplication)
  * Multiplies *AL/AX/EAX* by operand; stores result in *AX/DX:AX/EDX:EAX*.
      * *CF/OF* cleared if upper half of product is *zero*.
    
```assembly
MUL reg/mem
mov al, 5h
mov bl, 10h
mul bl      ; AX = 0050h, CF = 0
```
### `IMUL` (signed ...)
  * Multiplies signed operands; 
  * result sign depends on operand signs.
      * *CF/OF* set if result is *truncated* (upper half not a sign extension).
      * *1-Operand:* `IMUL reg/mem` (Same implicit registers as MUL).
      * *2-Operand:* `IMUL reg16, reg/mem16` (Dest \*= Src).
      * *3-Operand:* `IMUL reg16, reg/mem16, imm` (Dest = Src \* Imm).
    
    ```assembly
    imul bx, ax    ; BX = BX * AX
    imul bx, 2     ; BX = BX * 2
    imul bx, cx, 2 ; BX = CX * 2
    ```


## Division & Sign Extension

### **`DIV` (Unsigned Division)**
  - Divides *AX/DX:AX/EDX:EAX* by operand; Quotient in *AL/AX/EAX*, Remainder in *AH/DX/EDX*.

```assembly
DIV reg/mem
mov ax, 0083h ; Dividend
mov bl, 2     ; Divisor
div bl        ; AL = 41h (Quotient), AH = 01h (Remainder)
```
### `IDIV` (signed ...)
  * Same register usage as DIV but for signed integers.
      * *Crucial:* Dividend must be **sign-extended** before `IDIV`.
#### **Sign Extension Instructions:**
  * `CBW`: Extends *AL* sign into *AH* (`Byte` $\to$ `Word`).
  * `CWD`: Extends *AX* sign into *DX* (`Word` $\to$ `DWORD`).
  * `CDQ`: Extends *EAX* sign into *EDX* (`DWORD` $\to$ `QWORD`).

```assembly
mov al, -48 ; D0h
cbw         ; Extend AL to AH (AX = FFD0h)
mov bl, 5
idiv bl     ; AL = -9, AH = -3
```


## Extended Arithmetic

- Used for multi-byte/multi-word arithmetic operations.
### `ADC` (add with carry)

- Adds *`SRC`* + *`Dest`* + *`CF`*.
```assembly
ADC destination, source
add al, 0FFh ; Sets CF=1
adc dl, 0    ; Adds 0 + 0 + CF(1) to DL
```
### `SBB` (sub with borrow)
- Subtracts *Source* + *Carry Flag* from *Destination*.
```assembly
SBB destination, source
sub eax, 2 ; Sets CF if borrow needed
sbb edx, 0 ; Subtracts 0 + CF from EDX
```

### PROBLEM: Data scrambler

```
.code
main PROC
    ; Initialize
    mov ax, 0002h
    
    ; 1. Swap High/Low bytes
    rol ax, 8           ; AX becomes 0200h
    
    ; 2. Multiply by 16 using Shift
    shl ax, 4           ; AX becomes 2000h
    
    ; 3. Multiply by 10h (16) using MUL
    mov bx, 0010h
    mul bx              ; Result is 20000h -> DX=0002h, AX=0000h
    
    ; 4. Divide by 8 using DIV
    mov cx, 8
    div cx              ; 20000h / 8 = 4000h -> AX=4000h
    
    call DumpRegs
    exit
main ENDP
END main
```


# LAB 10: Advanced Procedures & Stack Frames




## Stack Applications

- **Save Area:** Temporary storage for *registers* to restore original values later.
- **Return Address:** `CALL` saves the address to return to after execution.
- **Arguments:** Input values are *pushed* onto the stack before calling.
- **Local Variables:** Storage for variables valid only *inside* the subroutine.

## Stack Parameters & Passing Methods

- **Pass by Value:** Pushes a *copy* of the value; original variable remains *unchanged*.
```assembly
push var1      ; Push value
call AddTwo
```
- **Pass by Reference:** Pushes the *offset* (address); allows modification of the *original* object (arrays/structures).
```assembly
push OFFSET arr ; Push address
call ArrayFill
```
- **Explicit Parameters:** Using `EQU` to name stack offsets for readability.

```assembly
x_param EQU [ebp + 8]
mov eax, x_param
```

## Manual Stack Frame Construction
- **Setup (Prologue):** Save old base pointer, set new base pointer.
```assembly
push ebp
mov ebp, esp
```
- **Access Parameters:** Positive offsets from EBP (e.g., `[ebp + 8]`).
- **Cleanup (Epilogue):** Restore stack and base pointer.
```assembly
pop ebp
ret
```
- **Stack Cleanup:** `ret n` removes *n* bytes of parameters from the stack upon return.
```assembly
ret 8 ; Pop EIP and add 8 to ESP
```

## Local Variables & LEA

- **Local Variables:** Created *below* EBP using negative offsets.
```assembly
sub esp, 8              ; Reserve space
mov [ebp - 4], 10       ; Assign value
```
### **`LEA` (Load Effective Address)** 
- Calculates address of indirect operands at *runtime*.
```assembly
lea esi, [ebp - 30]     ; Get address of local buffer
```

## Automation Instructions & Directives

#### **`ENTER`** 

- Automatically creates stack frame (replaces `push ebp`, `mov ebp, esp`, `sub esp`).
```assembly
enter 0, 0     ; 0 bytes for locals, nesting level 0
```
#### **`LEAVE`** 

- Reverses `ENTER` (replaces `mov esp, ebp`, `pop ebp`).
#### **`LOCAL` Directive** 

- High-level declaration of local variables; handles stack reservation automatically.
```assembly
LOCAL temp : DWORD
mov temp, 5
```

## Advanced Invocation & Prototypes

### **`INVOKE`** 
- Replaces `push` sequences + `call`; handles argument passing in one line.
```assembly
INVOKE procedureName, arg1, arg2
```
### **`ADDR`** 
- Passes a *pointer/address* when using `INVOKE`.
```assembly
INVOKE FillArray, ADDR myArray
```
### **`PROC` (Extended)** 
- Declares procedure with named parameters.
```assembly
FillArray PROC, pArray:PTR BYTE
```
### **`PROTO`** 
- Declares a function prototype (like a header file) for validation before definition.
```assembly
MySub PROTO :DWORD, :DWORD
```

## Recursion

- Procedures that call *themselves*.
- Requires a *termination condition* (Base case) to stop infinite loops.
    ```assembly
    CalcSum PROC
      cmp ecx, 0
      jz L2         ; Base case
      call CalcSum  ; Recursive call
    L2: ret
    CalcSum ENDP
    ```

# LAB 11: String Handling & 2D Arrays


## String Primitive Instructions

- **Concept:** Process memory sequences pointed to by **ESI** (Source Index) and **EDI** (Destination Index).
- **Efficiency:** Automatically repeat and adjust indexes based on the Direction Flag.

### Direction Flag Control

- **`CLD`:** *Clears* Direction flag, indices *increment* (Forward processing).
- **`STD`:** *Sets* Direction flag, indices *decrement* (Reverse processing).

### Repeat Prefixes (Uses ECX as counter)

- **`REP`:** Repeats instruction while ECX \> 0.
- **`REPE` / `REPZ`:** Repeats while *Equal* (ZF=1) and ECX \> 0.
- **`REPNE` / `REPNZ`:** Repeats while *Not Equal* (ZF=0) and ECX \> 0.

### The Instructions

#### `MOVSB` / `MOVSW` / `MOVSD` 
- Copies *Byte* / *Word* / *Doubleword* from **[ESI]** to **[EDI]**.
```assembly
mov esi, OFFSET string1
mov edi, OFFSET string2
mov ecx, SIZEOF string1
rep movsb ; Copy entire string
```
#### `CMPSB` / `CMPSW` / `CMPSD` 
- Compares *Byte* / *Word* / *Doubleword* at **[ESI]** with **[EDI]**.
```assembly
repe cmpsb ; Compare strings, stop at mismatch
```
#### `SCASB` / `SCASW` / `SCASD` 
- Compares **AL/AX/EAX** with value at **[EDI]** (Scans for specific value).
```assembly
mov al, 'F'
repne scasb ; Find 'F' in string pointed by EDI
```
#### `STOSB` / `STOSW` / `STOSD` 
- Stores **AL/AX/EAX** into memory at **[EDI]** (Fills array).
```assembly
mov al, 0FFh
rep stosb ; Fill buffer with 0FFh
```
#### `LODSB` / `LODSW` / `LODSD` 
- Loads memory from **[ESI]** into **AL/AX/EAX** (Rarely uses REP).
    ```assembly
    lodsd ; Load dword from [ESI] to EAX
    ```


## Irvine32 String Procedures

### `Str_compare`
- Compares two strings, sets flags (CF/ZF) for equality/ordering.
```assembly
INVOKE Str_compare, ADDR string1, ADDR string2
```
### `Str_length` 
- Returns string length in **EAX**.
```assembly
INVOKE Str_length, ADDR myString
```
### `Str_copy` 
- Copies null-terminated string from source to target.
```assembly
INVOKE Str_copy, ADDR source, ADDR target
```
### `Str_trim` 
- Removes specific trailing character from string.
```assembly
INVOKE Str_trim, ADDR string, 'o'
```
### `Str_ucase` 
- Converts string to uppercase.
```assembly
INVOKE Str_ucase, ADDR myString
```


## Two-Dimensional Arrays

- **Concept:** Abstract view of 1D memory; usually implemented in **Row-Major** order.
- **Base-Index Operand:** Address calculated as `[base + index]`.
```assembly
mov ax, [ebx + esi]
```
- **Row-Major Calculation:** `Offset = Base + (Row_Index * Row_Size) + (Col_Index * Element_Size)`.
- **Base-Index-Displacement:** Combines displacement, base, and index.
```assembly
mov eax, [ebx + esi + 10]
```


## Searching & Sorting

- **Bubble Sort:** Compares adjacent pairs (0 and 1), swaps if in reverse order, repeats until sorted.
