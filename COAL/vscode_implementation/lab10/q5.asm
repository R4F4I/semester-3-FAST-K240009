;Write a program that calculates factorial of a given number n. Make a recursive procedure
;named Fact that takes n as an input parameter.
INCLUDE Irvine32.inc

.data
prompt      BYTE "Enter a number to calculate its factorial: ", 0
resultMsg   BYTE "Factorial result: ", 0
errorMsg    BYTE "Error: Number too large or negative!", 0
newline     BYTE 0Dh, 0Ah, 0

.code

; Requires: n >= 0, n <= 12 (to prevent overflow in DWORD)
; Method: EBP Stack Frame (Method A)
;--------------------------------------------------------------------
Fact PROC
    PUSH EBP
    MOV EBP, ESP
    
    ; Save volatile registers
    PUSH EBX
    
    ; Get parameter n from stack
    MOV EAX, [EBP + 8]      ; n is at EBP+8
    
    ; Base case: if n <= 1, return 1
    CMP EAX, 1
    JBE FactBaseCase
    
    ; Recursive case: n * Fact(n-1)
    MOV EBX, EAX            ; Save n in EBX
    DEC EAX                 ; Calculate n-1
    PUSH EAX                ; Push (n-1) as parameter
    CALL Fact               ; Recursive call, result in EAX
    
    ; Multiply n * Fact(n-1)
    MUL EBX                 ; EAX = EAX * EBX = Fact(n-1) * n
    JMP FactEnd
    
FactBaseCase:
    MOV EAX, 1              ; Return 1 for base case
    
FactEnd:
    ; Restore volatile registers
    POP EBX
    
    ; Epilogue
    POP EBP
    RET 4                   ; Clean up 4 bytes (1 DWORD parameter)
Fact ENDP

;--------------------------------------------------------------------
; main - Entry point
;--------------------------------------------------------------------
main PROC
    ; Display prompt
    MOV EDX, OFFSET prompt
    CALL WriteString
    
    ; Read integer from user
    CALL ReadInt            ; Result in EAX
    
    ; Validate input (0 <= n <= 12)
    CMP EAX, 0
    JL InputError
    CMP EAX, 12
    JG InputError
    
    ; Call Fact(n)
    PUSH EAX                ; Push n as parameter
    CALL Fact               ; Result returned in EAX
    
    ; Save result before I/O
    PUSH EAX
    
    ; Display result message
    MOV EDX, OFFSET resultMsg
    CALL WriteString
    
    ; Restore and display result
    POP EAX
    CALL WriteDec
    
    ; Print newline
    MOV EDX, OFFSET newline
    CALL WriteString
    
    JMP ProgramEnd
    
InputError:
    MOV EDX, OFFSET errorMsg
    CALL WriteString
    MOV EDX, OFFSET newline
    CALL WriteString
    
ProgramEnd:
    exit
main ENDP

END main