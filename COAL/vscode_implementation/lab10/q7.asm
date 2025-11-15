;Write a program to take 4 input numbers from the users. Then make two procedures
;CheckPrime and LargestPrime. The program should first check if a given number is a prime
;number or not. If all of the input numbers are prime numbers then the program should call the
;procedure LargestPrime.
;CheckPrime: This procedure tests if a number is prime or not LargestPrime: This procedure finds
;and displays the largest of the four prime numbers.

INCLUDE Irvine32.inc

.data
prompt1         BYTE "Enter number 1: ", 0
prompt2         BYTE "Enter number 2: ", 0
prompt3         BYTE "Enter number 3: ", 0
prompt4         BYTE "Enter number 4: ", 0
notPrimeMsg     BYTE " is not a prime number!", 0
allPrimeMsg     BYTE "All numbers are prime!", 0
largestMsg      BYTE "The largest prime is: ", 0
newline         BYTE 0Dh, 0Ah, 0

num1            DWORD ?
num2            DWORD ?
num3            DWORD ?
num4            DWORD ?

.code

CheckPrime PROC
    ; === Prologue: Establish Stack Frame ===
    PUSH EBP
    MOV EBP, ESP
    
    ; === Save Volatile Registers ===
    PUSH EBX
    PUSH ECX
    PUSH EDX
    
    ; === Get Parameter ===
    MOV EAX, [EBP + 8]      ; Get n
    
    ; === Handle Edge Cases ===
    CMP EAX, 2              ; If n < 2, not prime
    JB NotPrime
    CMP EAX, 2              ; If n == 2, it's prime
    JE IsPrime
    
    ; === Check if Even (not prime if even) ===
    TEST EAX, 1             ; Test least significant bit
    JZ NotPrime             ; If even (LSB=0), not prime
    
    ; === Trial Division: Test divisors from 3 to sqrt(n) ===
    MOV EBX, EAX            ; EBX = n (number to test)
    MOV ECX, 3              ; ECX = divisor, start at 3
    
CheckLoop:
    ; Check if ECX * ECX > n (i.e., ECX > sqrt(n))
    MOV EAX, ECX
    MUL ECX                 ; EAX = ECX * ECX
    CMP EAX, EBX            ; Compare ECX^2 with n
    JA IsPrime              ; If ECX^2 > n, no divisors found, is prime
    
    ; Test if n is divisible by ECX
    MOV EAX, EBX            ; EAX = n
    XOR EDX, EDX            ; Clear EDX for division
    DIV ECX                 ; EAX = n / ECX, EDX = remainder
    
    CMP EDX, 0              ; Check remainder
    JE NotPrime             ; If remainder = 0, divisible, not prime
    
    ADD ECX, 2              ; Next odd divisor
    JMP CheckLoop
    
IsPrime:
    MOV EAX, 1              ; Return 1 (true)
    JMP CheckEnd
    
NotPrime:
    MOV EAX, 0              ; Return 0 (false)
    
CheckEnd:
    ; === Restore Volatile Registers ===
    POP EDX
    POP ECX
    POP EBX
    
    ; === Epilogue: Tear Down Stack Frame ===
    POP EBP
    RET 4                   ; Clean up 4 bytes (1 parameter)
CheckPrime ENDP

LargestPrime PROC
    ; === Prologue: Establish Stack Frame ===
    PUSH EBP
    MOV EBP, ESP
    
    ; === Save Volatile Registers ===
    PUSH EBX
    
    ; === Get Parameters (LIFO: last pushed is first accessed) ===
    MOV EAX, [EBP + 8]      ; num4 (pushed last)
    MOV EBX, [EBP + 12]     ; num3
    MOV ECX, [EBP + 16]     ; num2
    MOV EDX, [EBP + 20]     ; num1 (pushed first)
    
    ; === Find Maximum ===
    ; Start with num1 as current max
    MOV EAX, EDX            ; EAX = num1
    
    ; Compare with num2
    CMP EAX, ECX
    JGE CheckNum3           ; If num1 >= num2, check next
    MOV EAX, ECX            ; Else, num2 is new max
    
CheckNum3:
    ; Compare with num3
    CMP EAX, EBX
    JGE CheckNum4           ; If current >= num3, check next
    MOV EAX, EBX            ; Else, num3 is new max
    
CheckNum4:
    ; Compare with num4
    MOV EBX, [EBP + 8]      ; Get num4
    CMP EAX, EBX
    JGE DisplayMax          ; If current >= num4, we have max
    MOV EAX, EBX            ; Else, num4 is max
    
DisplayMax:
    ; === Display Result (Save EAX before I/O) ===
    PUSH EAX                ; Save max value
    
    MOV EDX, OFFSET largestMsg
    CALL WriteString
    
    POP EAX                 ; Restore max value
    CALL WriteDec
    
    MOV EDX, OFFSET newline
    CALL WriteString
    
    ; === Restore Volatile Registers ===
    POP EBX
    
    ; === Epilogue: Tear Down Stack Frame ===
    POP EBP
    RET 16                  ; Clean up 16 bytes (4 parameters)
LargestPrime ENDP

main PROC
    ; === Input: Get 4 numbers from user ===
    MOV EDX, OFFSET prompt1
    CALL WriteString
    CALL ReadInt
    MOV num1, EAX
    
    MOV EDX, OFFSET prompt2
    CALL WriteString
    CALL ReadInt
    MOV num2, EAX
    
    MOV EDX, OFFSET prompt3
    CALL WriteString
    CALL ReadInt
    MOV num3, EAX
    
    MOV EDX, OFFSET prompt4
    CALL WriteString
    CALL ReadInt
    MOV num4, EAX
    
    ; === Check if num1 is prime ===
    PUSH num1
    CALL CheckPrime
    CMP EAX, 0
    JE Num1NotPrime
    
    ; === Check if num2 is prime ===
    PUSH num2
    CALL CheckPrime
    CMP EAX, 0
    JE Num2NotPrime
    
    ; === Check if num3 is prime ===
    PUSH num3
    CALL CheckPrime
    CMP EAX, 0
    JE Num3NotPrime
    
    ; === Check if num4 is prime ===
    PUSH num4
    CALL CheckPrime
    CMP EAX, 0
    JE Num4NotPrime
    
    ; === All are prime! ===
    MOV EDX, OFFSET allPrimeMsg
    CALL WriteString
    MOV EDX, OFFSET newline
    CALL WriteString
    
    ; === Find and display largest prime ===
    PUSH num1               ; Push in order: num1, num2, num3, num4
    PUSH num2
    PUSH num3
    PUSH num4
    CALL LargestPrime
    
    JMP ProgramEnd
    
    ; === Error Handlers ===
Num1NotPrime:
    MOV EAX, num1
    CALL WriteDec
    MOV EDX, OFFSET notPrimeMsg
    CALL WriteString
    MOV EDX, OFFSET newline
    CALL WriteString
    JMP ProgramEnd
    
Num2NotPrime:
    MOV EAX, num2
    CALL WriteDec
    MOV EDX, OFFSET notPrimeMsg
    CALL WriteString
    MOV EDX, OFFSET newline
    CALL WriteString
    JMP ProgramEnd
    
Num3NotPrime:
    MOV EAX, num3
    CALL WriteDec
    MOV EDX, OFFSET notPrimeMsg
    CALL WriteString
    MOV EDX, OFFSET newline
    CALL WriteString
    JMP ProgramEnd
    
Num4NotPrime:
    MOV EAX, num4
    CALL WriteDec
    MOV EDX, OFFSET notPrimeMsg
    CALL WriteString
    MOV EDX, OFFSET newline
    CALL WriteString
    
ProgramEnd:
    exit
main ENDP

END main