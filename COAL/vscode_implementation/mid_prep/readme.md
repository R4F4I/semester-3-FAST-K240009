This document provides 12 comprehensive Assembly Language (ASM) programming tasks, based on the provided course materials (`COAL LAB 01-06`), followed by their complete solutions using the MASM syntax and the Irvine32 library.

-----

# ASSEMBLY LANGUAGE TASKS (1-12)

## Problems

---
### **Problem 1: Register Tracing and Prediction (L01/L02)**

Predict the final value of the `EAX` and `EBX` registers after the execution of the following assembly code snippet. Assume all registers are 32-bit.

```assembly
; Initial state: EAX = 0, EBX = 0
.code
  mov eax, 1000h
  mov ebx, 0FFFFh
  add eax, 20h
  sub ebx, eax
  ; Final Value of EAX?
  ; Final Value of EBX?
```

---
### **Problem 2: Mixed-Format Arithmetic (L02/L03)**

Write an assembly program snippet to compute the following expression and store the final 32-bit result in the `EAX` register. Use the appropriate representation for each number format (binary `b`, hexadecimal `h`, and decimal).

$$EAX = (1010110b) + (1A0h) - (20\text{ decimal})$$

---
### **Problem 3: Data Definition and Sizing Operators (L03/L05)**

Define the following data in the `.data` section and then write assembly code to calculate specific memory metrics using the `SIZEOF` operator.

1.  A null-terminated string `string_msg` initialized to `"Welcome to COAL Lab!"`.
2.  A word array `array_word` containing 5 uninitialized words and 3 words initialized to the values 1, 2, and 3 respectively, using the `DUP` operator.

*Required calculations in the `.code` section:*
a) Calculate the total size in bytes of `array_word` and store it in `EBX`.
b) Calculate the number of characters in `string_msg` (excluding the null terminator) and store it in `ECX`.

---
### **Problem 4: Data Transfer and Sign/Zero Extension (L04)**

Given the following variables, write an assembly code snippet that performs the following three steps:

```assembly
.data
  byteVal SBYTE -1  ; -1 is FFh in SBYTE
  wordVal WORD 1000h
```

1.  Move the unsigned value of `byteVal` into the 32-bit register `EAX`, ensuring the upper bits are cleared (`EAX` should hold `000000FFh`).
2.  Move the signed value of `byteVal` into `EBX`, ensuring the sign is correctly extended (`EBX` should hold `FFFFFFFFh`).
3.  Exchange the value of `wordVal` with the low 16-bits of `ECX` (`CX`).

---
### **Problem 5: High-Level Expression Translation (L04)**

Translate the following high-level arithmetic statement into efficient x86 assembly language code. The variables are all 32-bit signed integers (`SDWORD`), and the final result must be stored in `EAX`.

$$EAX = (A - B) + C - (D + 5)$$

*Variables:*

```assembly
.data
  A SDWORD 50
  B SDWORD 10
  C SDWORD 5
  D SDWORD 2
```

---
### **Problem 6: Flag Register Analysis (L05)**

Determine the final state of the **Zero Flag (ZF)**, **Sign Flag (SF)**, **Carry Flag (CF)**, and **Overflow Flag (OF)** after the execution of each of the following independent instructions.

| Instruction | Initial State | ZF | SF | CF | OF |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `add al, 70h` | `AL = 90h` | ? | ? | ? | ? |
| `sub al, al` | `AL = 90h` | ? | ? | ? | ? |
| `add bl, bl` | `BL = 80h` | ? | ? | ? | ? |

---
### **Problem 7: Indexed and Indirect Addressing (L05)**

Given the following 32-bit array of integers:

```assembly
.data
  scores DWORD 100, 95, 80, 75
```

Write an assembly code snippet to perform the following:

1.  Use the `OFFSET` operator to load the base address of `scores` into the `ESI` register.
2.  Access the third element (value **80**) of the array using **direct-offset addressing** (`[ESI + offset]`) and move it into `EAX`.
3.  Access the first element (value **100**) using **indirect addressing** (`[ESI]`) and move it into `EBX`.

---
### **Problem 8: Irvine Library I/O (L06)**

Write a complete Assembly program that prompts the user to enter a signed integer, reads the input using an Irvine32 procedure, and then displays the input integer multiplied by **5**. Use `ReadInt`, `WriteDec`, and `WriteString`.

---
### **Problem 9: Conditional Logic (L06)**

Write an assembly code snippet that compares two 32-bit variables, `num1` and `num2`, and implements the following control flow using `CMP` and a conditional jump:

  - If `num1` is **greater than or equal to** `num2`, jump to a label `L1_GreaterEqual`.
  - Otherwise, jump to a label `L2_Lesser`.

*Variables:*

```assembly
.data
  num1 DWORD 50
  num2 DWORD 100
```

The labels should simply set the `EAX` register to a distinct value to confirm the flow path.

---
### **Problem 10: Loop Structure (L06)**

Write an assembly code snippet to calculate the sum of the first 10 positive integers ($1 + 2 + 3 + ... + 10$). The loop must use the `LOOP` instruction. Store the final sum in `EAX`.

---
### **Problem 11: Nested Loops and Console Output (L06)**

Write an assembly code snippet that uses **nested loops** to display the following 5x5 pattern of asterisks on the console, starting at position (0, 0). Use Irvine32 procedures like `Gotoxy` and `WriteString`.

```
*****
*****
*****
*****
*****
```

---
### **Problem 12: Integrated Program: Positive Integer Sum (L06)**

Write a complete assembly program that:

1.  Reads a non-negative integer **N** from the user.
2.  If **N** is zero, displays the message "Input must be positive." and exits.
3.  If **N** is positive, calculates the sum of all integers from 1 up to **N** (i.e., $1+2+...+N$).
4.  Displays the final calculated sum using `WriteDec`.

-----


## Solutions

---
### **Solution 1: Register Tracing and Prediction**

| Instruction | EAX | EBX | Explanation |
| :--- | :--- | :--- | :--- |
| `mov eax, 1000h` | `1000h` | `0000FFFFh` | Load initial value. |
| `mov ebx, 0FFFFh` | `1000h` | `0000FFFFh` | Load initial value. |
| `add eax, 20h` | `1020h` | `0000FFFFh` | $1000h + 20h = 1020h$. |
| `sub ebx, eax` | `1020h` | **`0000EFDh`** | $0FFFFh - 1020h = 0EFDh$. |

  * **Final Value of EAX: `1020h`**
  * **Final Value of EBX: `EFDh`**

---
### **Solution 2: Mixed-Format Arithmetic**

$$EAX = (1010110b) + (1A0h) - (20\text{ decimal})$$

  * $1010110b = 42h$
  * $20\text{ decimal} = 14h$
  * $EAX = 42h + 1A0h - 14h = 1E2h - 14h = 1CEh$

<!-- end list -->

```assembly
; Problem 2 Solution
INCLUDE Irvine32.inc
.code
main PROC
  ; EAX = (1010110b) + (1A0h) - (20 decimal)
  
  mov eax, 1010110b    ; EAX = 42h
  add eax, 1A0h        ; EAX = 1E2h
  sub eax, 20          ; EAX = 1CEh (20 is decimal)
  
  exit
main ENDP
END main
```

---
### **Solution 3: Data Definition and Sizing Operators**

```assembly
; Problem 3 Solution
INCLUDE Irvine32.inc
.data
  ; 1. Null-terminated string (20 chars + 1 null terminator = 21 bytes)
  string_msg BYTE "Welcome to COAL Lab!", 0
  
  ; 2. Word array (5 uninit words + 3 init words = 8 words * 2 bytes/word = 16 bytes)
  array_word WORD 5 DUP(?), 1, 2, 3
  
.code
main PROC
  ; a) Calculate total size in bytes of array_word
  mov ebx, SIZEOF array_word  ; EBX = 16
  
  ; b) Calculate number of elements (characters) in string_msg
  mov ecx, SIZEOF string_msg  ; ECX = 21 (Total bytes including null)
  dec ecx                     ; ECX = 20 (Total characters excluding null)
  
  exit
main ENDP
END main
```

---
### **Solution 4: Data Transfer and Sign/Zero Extension**

```assembly
; Problem 4 Solution
INCLUDE Irvine32.inc
.data
  byteVal SBYTE -1  ; FFh
  wordVal WORD 1000h
  
.code
main PROC
  ; Assume ECX is initialized, e.g., to 2000h
  mov ecx, 2000h 
  
  ; 1. Move unsigned value of byteVal to EAX (Zero Extension)
  movzx eax, byteVal    ; EAX = 000000FFh
  
  ; 2. Move signed value of byteVal to EBX (Sign Extension)
  movsx ebx, byteVal    ; EBX = FFFFFFFFh
  
  ; 3. Exchange the value of wordVal with the low 16-bits of ECX (CX)
  xchg cx, wordVal      ; CX becomes 1000h, wordVal becomes 2000h
  
  exit
main ENDP
END main
```

---
### **Solution 5: High-Level Expression Translation**

$$EAX = (A - B) + C - (D + 5)$$

```assembly
; Problem 5 Solution
INCLUDE Irvine32.inc
.data
  A SDWORD 50
  B SDWORD 10
  C SDWORD 5
  D SDWORD 2
  
.code
main PROC
  ; EAX = (A - B)
  mov eax, A
  sub eax, B          ; EAX = 40
  
  ; EAX = EAX + C
  add eax, C          ; EAX = 45
  
  ; Calculate (D + 5) in a temporary register (EBX)
  mov ebx, D
  add ebx, 5          ; EBX = 7
  
  ; EAX = EAX - (D + 5)
  sub eax, ebx        ; EAX = 45 - 7 = 38
  
  exit
main ENDP
END main
```

---
### **Solution 6: Flag Register Analysis**

*Initial states:* `90h` = 10010000b (signed -112); `80h` = 10000000b (signed -128).

| Instruction | Result | ZF | SF | CF | OF | Explanation |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| `add al, 70h` | `00h` (Result: $90h + 70h = 100h$) | **1** | **0** | **1** | **0** | Result is zero (ZF=1). Carry out (CF=1). No signed overflow ($-112 + 112 = 0$). |
| `sub al, al` | `00h` (Result: $90h - 90h = 0h$) | **1** | **0** | **0** | **0** | Result is zero (ZF=1). No borrow (CF=0). |
| `add bl, bl` | `00h` (Result: $80h + 80h = 100h$) | **1** | **0** | **1** | **1** | Result is zero (ZF=1). Carry out (CF=1). Signed overflow: $-128 + (-128) = -256$, which is outside the SBYTE range ($-128$ to $127$). |

---
### **Solution 7: Indexed and Indirect Addressing**

```assembly
; Problem 7 Solution
INCLUDE Irvine32.inc
.data
  scores DWORD 100, 95, 80, 75
  
.code
main PROC
  ; 1. Load base address of scores into ESI
  mov esi, OFFSET scores
  
  ; 2. Access the third element (80) using direct-offset addressing
  ; The third element (index 2) is at an offset of 8 bytes (2 * SIZEOF DWORD)
  mov eax, [esi + 8]    ; EAX = 80
  
  ; 3. Access the first element (100) using indirect addressing [ESI]
  mov ebx, [esi]        ; EBX = 100
  
  exit
main ENDP
END main
```

---
### **Solution 8: Irvine Library I/O**

```assembly
; Problem 8 Solution (Reads N, displays N * 5)
TITLE Signed Integer Input/Output (Prob8.asm)
INCLUDE Irvine32.inc
.data
  promptMsg BYTE "Enter a signed integer: ", 0
  resultMsg BYTE "The result is: ", 0
  
.code
main PROC
  ; 1. Prompt user
  mov edx, OFFSET promptMsg
  call WriteString
  
  ; 2. Read signed integer into EAX
  call ReadInt            ; EAX = N
  
  ; 3. Multiply EAX by 5
  mov ebx, 5              
  mul ebx                 ; EAX = EAX * 5 (Result safely in EAX)
  
  ; 4. Display result message and value
  mov edx, OFFSET resultMsg
  call WriteString
  call WriteDec
  call Crlf
  
  exit
main ENDP
END main
```

---
### **Solution 9: Conditional Logic**

```assembly
; Problem 9 Solution
INCLUDE Irvine32.inc
.data
  num1 DWORD 50
  num2 DWORD 100
  
.code
main PROC
  mov eax, num1
  mov ebx, num2
  
  ; Compare num1 to num2
  cmp eax, ebx
  
  ; If num1 >= num2 (Greater or Equal), jump
  jge L1_GreaterEqual
  
  ; If num1 < num2 (Lesser) - This is the default fall-through path
  jmp L2_Lesser         
  
L1_GreaterEqual:
  ; This block executes if num1 >= num2
  mov eax, 1            ; EAX = 1 (Condition met)
  jmp L_Exit
  
L2_Lesser:
  ; This block executes if num1 < num2 (Expected path for 50 < 100)
  mov eax, 0            ; EAX = 0 (Condition not met)
  
L_Exit:
  ; EAX holds 0, confirming num1 < num2
  
  exit
main ENDP
END main
```

---
### **Solution 10: Loop Structure**

```assembly
; Problem 10 Solution (Sum of 1 to 10)
INCLUDE Irvine32.inc
.code
main PROC
  ; Calculate sum of 1 to 10 using LOOP
  
  mov ecx, 10       ; ECX = Loop counter (N)
  mov eax, 0        ; EAX = Accumulator for the sum
  
L_Loop:
  add eax, ecx      ; Add the current counter value (10, 9, 8, ..., 1) to EAX
  loop L_Loop       ; Decrements ECX, jumps if ECX != 0
  
  ; Final EAX = 55
  
  exit
main ENDP
END main
```

---
### **Solution 11: Nested Loops and Console Output**

```assembly
; Problem 11 Solution (5x5 Asterisk Pattern)
TITLE Nested Loop Pattern (Prob11.asm)
INCLUDE Irvine32.inc
.data
  asterisk BYTE "*", 0
  
.code
main PROC
  mov ecx, 5        ; Outer loop counter: 5 rows
  mov esi, 0        ; ESI for row number (0 to 4)

OuterLoop:
  push ecx          ; Save outer loop counter (ECX is needed by LOOP)
  
  mov ebx, 5        ; EBX = Inner loop counter: 5 columns
  mov edi, 0        ; EDI for column number (0 to 4)
  
InnerLoop:
  ; Set cursor position: DH = Row (ESI), DL = Column (EDI)
  mov dh, sil       ; Low byte of ESI (Row)
  mov dl, dil       ; Low byte of EDI (Column)
  call Gotoxy
  
  ; Display asterisk
  mov edx, OFFSET asterisk
  call WriteString
  
  inc edi           ; Next column
  dec ebx           ; Decrement inner loop counter
  jnz InnerLoop     ; Jump if EBX != 0
  
  ; Cleanup and next row
  pop ecx           ; Restore outer loop counter
  inc esi           ; Next row
  loop OuterLoop    ; Decrement ECX, jump if not zero
  
  exit
main ENDP
END main
```

---
### **Solution 12: Integrated Program: Positive Integer Sum**

```assembly
; Problem 12 Solution (Reads N, calculates 1+..+N)
TITLE Integrated Sum Program (Prob12.asm)
INCLUDE Irvine32.inc
.data
  promptN   BYTE "Enter a non-negative integer N: ", 0
  errorMsg  BYTE "Input must be positive.", 0
  resultMsg BYTE "The sum from 1 to N is: ", 0
  
.code
main PROC
  ; 1. Read N from the user
  mov edx, OFFSET promptN
  call WriteString
  call ReadInt            ; EAX = N
  
  ; 2. Check if N <= 0
  cmp eax, 1              ; Compare N with 1
  jl L_Error              ; If N < 1 (less than), jump to error (covers 0 and negative)
  
  ; 3. Calculate sum 1 to N
  mov ecx, eax            ; ECX = N (loop counter)
  mov eax, 0              ; EAX = Sum accumulator (0)
  
L_SumLoop:
  add eax, ecx            ; Sum = Sum + N
  loop L_SumLoop          ; Decrement ECX, loop until ECX = 0
  
  ; 4. Display the result
  mov edx, OFFSET resultMsg
  call WriteString
  call WriteDec           ; Displays EAX (the sum)
  call Crlf
  jmp L_Exit

L_Error:
  ; Display error message and exit
  mov edx, OFFSET errorMsg
  call WriteString
  call Crlf
  
L_Exit:
  exit
main ENDP
END main
```