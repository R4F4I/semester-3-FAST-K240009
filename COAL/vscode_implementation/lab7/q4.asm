
; Q4 Write the following C program and then convert it into Assembly language
; using CMP and conditional jump instructions (JG, JL, JGE, etc.):
; 
; #include <stdio.h>
; 
; int main() {
;     int a, b;
;     printf("Enter two numbers: ");
;     scanf("%d %d", &a, &b);
;     if (a > b && a < 100)
;        printf("Condition True\n");
;     else
;        printf("Condition False\n");
;     return 0;
; }





INCLUDE Irvine32.inc

.data
; Variables to store the user's input
a SDWORD ?
b SDWORD ?

; Strings for user interaction and output
promptA BYTE "Enter a: ", 0
promptB BYTE "Enter b: ", 0
trueMsg   BYTE "Condition True", 0
falseMsg  BYTE "Condition False", 0

.code
main PROC
    ; Display the prompt for the user
    mov edx, OFFSET promptA
    call WriteString

    ; Read the first integer and store it in variable 'a'
    call ReadInt
    mov a, eax


    ; Display the prompt for the user
    mov edx, OFFSET promptB
    call WriteString

    ; Read the second integer and store it in variable 'b'
    call ReadInt
    mov b, eax

    ; Now, implement the conditional logic: if(a > b && a < 100)
    ; a > b.
    mov eax, a
    cmp eax, b
    jle IsFalse ; Jump if Less or Equal (a <= b), which makes the condition false.

    ; didn't jump, a > b  true.
    ; AND check: a < 100.
    cmp eax, 100
    jge IsFalse ; Jump if Greater or Equal (a >= 100), which makes the condition false.

    ; If we didn't jump again, then both are true.
IsTrue:
    mov edx, OFFSET trueMsg
    call WriteString
    call Crlf
    jmp EndProgram ; Skip 'IsFalse'

IsFalse:
    ; This block is executed if either of the conditions fails.
    mov edx, OFFSET falseMsg
    call WriteString
    call Crlf

EndProgram:
    exit

main ENDP
END main