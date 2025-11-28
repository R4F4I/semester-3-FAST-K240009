---
title: COAL_lab_final_notes
date: November 27, 2025
datenum: 20251127
day: Thursday
time: 2025-11-27T09:30:42+05:00
UNIX timestamp: 1764217842
from: FAST
field: BSAI
semester: 3
aliases: []
tags: []
type:
  - notes
  - study
  - university
  - classwork
note-level: 1
author:
  - Rafay Siddiqui | 24K-0009
abstract: this is an abstract
description:
course: EL2003-COAL
class:
cssclasses:
  - center-titles
  - image-borders
---


<span style="font-style:italic; font-weight:bold; color:rgb(255, 0, 0)">Topic:</span> **COAL_lab_final_notes**

****<span style="font-weight:bold; font-weight:bold; color:rgb(255, 192, 0)">File Creation Date:</span>** Nov 27, 2025 // Thursday //  09:30 

<font color="#548dd4">Last Modified:</font>  Nov 27, 2025 // Thursday //  09:30

**<span style="font-weight:bold; color:rgb(146, 208, 80)">Course:</span>** 
**<span style="font-weight:bold; font-weight:bold; color:rgb(0, 176, 240)">Class:</span>** 

---

# References
- item

# Notes

## LAB 7 -Conditional Jumps And Processing


### Learning Objectives
a. Boolean and Comparison Instructions
b. Conditional Jumps
c. Conditional Loop Instructions
d. Conditional Structures

#### ***Boolean and Comparison Instructions***
A programming language that permits decision making lets you alter the flow of
control, using a technique known as conditional branching.


- ***AND Instruction***
	- It is boolean AND operation between a source operand and destination operand. If both bits equal 1, the result bit is 1; otherwise, it is 0. The operands can be 8, 16, or 32 bits, and they must be the same size.

Syntax: 
```
AND reg, reg
AND reg, mem
AND reg, imm
AND mem, reg
AND mem, imm

```

The AND instruction always clears the Carry and Overflow flags. It modifies the Sign,
Zero, and Parity flags in a way that is consistent with the value assigned to the destination
operand.
>[!note] The All other instructions use the same operand combinations and sizes as the AND instruction.

- ***OR Instruction***
- It is boolean AND operation between a source operand and destination operand. For each matching bit in the two operands, the output bit is 1 when at least one of the input bits is 1.


```
mov al,11100011b
or al,00000100b ; result in AL = 11100111
```
- The OR instruction always clears the Carry and Overflow flags. It modifies the Sign,
Zero, and Parity flags in a way that is consistent with the value assigned to the destination operand.

- ***XOR Instruction***
- The XOR instruction performs a boolean exclusive-OR operation between each pair of
matching bits in two operands and stores the result in the destination operand. If both
bits are the same (both 0 or both 1), the result is 0; otherwise, the result is 1.
The XOR instruction always clears the Overflow and Carry flags. XOR modifies the
Sign, Zero, and Parity flags.
- NOT Instruction
The NOT instruction toggles (inverts) all bits in an operand. The result is called the one’s
complement.

Syntax: 
```
NOT reg
NOT mem
```


```
mov al, 11110000b
xor al ; al = 00001111b
```

- TEST Instruction
The TEST instruction performs an implied AND operation between each pair of
matching bits in two operands and sets the Sign, Zero, and Parity flags based on the value
assigned to the destination operand.
The only difference between TEST and AND is that TEST does not modify the
destination operand.
Testing Multiple Bits: The TEST instruction can check several bits at once. Suppose we
want to know whether bit 0 or bit 3 is set in the AL register. We can use the following
instruction to find this out:

EXAMPLE
.code
mov al, 10101110b ; Clear only bit 3
and al, 11110110b ; AL = 10100110
mov al, 11100011b ; set bit 2
or al, 00000100b ; AL = 11100111
mov al, 10110101b ; 5 bits means odd parity
xor al, 0 ;PF=0(PO)
mov al, 10100101b ; 4 bits means even parity
xor al, 0 ;PF=1(PE)

Page
| 3

mov
not
al, 11110000b
al ; AL = 00001111b
mov al, 00100101b
test al, 00001001b ;ZF=0
mov al, 00100101b
test al, 00001000b ;ZF=1
call
exit
DumpRegs

- CMP Instruction
CMP (compare) instruction performs an implied subtraction of a source operand from
a destination operand for comparison. Neither operand is modified.
Syntax:

CMP destination, source

Flags: The CMP instruction changes the Overflow, Sign, Zero, Carry, Auxiliary Carry,
and Parity flags according to the value the destination operand.
When two unsigned operands are compared, the Zero and Carry flags indicate
the following relations between operands:

Destination < source
Destination > source
Destination = source

ZF=0 CF=1
ZF=0 CF=0
ZF=1 CF=0

When two signed operands are compared, the Sign, Zero, and Overflow flags indicate the
following relations between operands:

Destination < source SF!=OF
Destination > source SF=OF
Destination = source ZF=1

Examples: Let’s look at three code fragments showing how flags are affected by the CMP
instruction.
.code
mov ax, 5

Page
| 4

cmp ax, 10 ; ZF = 0 and CF = 1

Page
| 5

mov
cmp
ax, 1000
ax, 1000 ;ZF=1 and CF =0
mov
cmp
si, 106
si, 0 ;ZF=0 and CF=0

- Conditional Jumps
1. an operation such as CMP, AND, or SUB modifies the CPU status flags.
2. a conditional jump instruction tests the flags and causes a branch to a new address.
- Jcond Instruction
A conditional jump instruction branches to a destination label when a status flag condition
is true.
Syntax:
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
| JG       |             |
| JNG      |             |
| JGE      |             |
| JNGE     |             |
| JL       |             |
| JNL      |             |
| JLE      |             |
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

Conditional Loop Instructions
- LOOPZ and LOOPE Instructions
The LOOPZ (loop if zero) instruction works just like the LOOP instruction except that
it has one additional condition: The Zero flag must be set in order for control to transfer
to the destination label.
The syntax is

LOOPZ destination

The LOOPE (loop if equal) instruction is equivalent to LOOPZ and they share the
same opcode.

- LOOPNZ and LOOPNE Instructions
The LOOPNZ (loop if not zero) instruction is the counterpart of LOOPZ. The loop
continues while the unsigned value of ECX is greater than zero (after being
decremented) and the Zero flag is clear.
The syntax is LOOPNZ destination
The LOOPNE (loop if not equal) instruction is equivalent to LOOPNZ and they share the
same opcode.
Example:
; The following take input from user until user press 0

.code
mov ecx,5
L1:
CALL readInt
cmp eax, 0
LOOPNZ L1
call DumpRegs
- Conditional Structures
We define a conditional structure to be one or more conditional expressions that
trigger a choice between different logical branches. Each branch causes a different
sequence of instructions to execute.
- Block-Structured IFStatements
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
cmp eax, o2 (o1==o2)?
jne l1 no: skip to l1

mov x, 1
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

