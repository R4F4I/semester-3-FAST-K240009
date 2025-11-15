;Write a non-recursive version of the procedure Fact that uses a loop to calculate factorial of
;given number n. Compare efficiency of both versions of the Fact procedure using GetMSeconds.

INCLUDE Irvine32.inc

.data
prompt          BYTE "Enter a number to calculate its factorial: ", 0
recursiveMsg    BYTE "Recursive Fact result: ", 0
iterativeMsg    BYTE "Iterative Fact result: ", 0
recursiveTime   BYTE "Recursive time (ms): ", 0
iterativeTime   BYTE "Iterative time (ms): ", 0
iterations      BYTE "Performance test iterations: ", 0
errorMsg        BYTE "Error: Number too large or negative!", 0
newline         BYTE 0Dh, 0Ah, 0
testIterations  DWORD 100000    ; Number of iterations for performance test

.code


FactRecursive PROC
    PUSH EBP
    MOV EBP, ESP
    PUSH EBX
    
    MOV EAX, [EBP + 8]      ; Get parameter n
    
    ; Base case: if n <= 1, return 1
    CMP EAX, 1
    JBE RecBaseCase
    
    ; Recursive case: n * FactRecursive(n-1)
    MOV EBX, EAX            ; Save n
    DEC EAX                 ; n-1
    PUSH EAX                ; Push parameter
    CALL FactRecursive      ; Recursive call
    MUL EBX                 ; EAX = Fact(n-1) * n
    JMP RecEnd
    
RecBaseCase:
    MOV EAX, 1
    
RecEnd:
    POP EBX
    POP EBP
    RET 4
FactRecursive ENDP
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
FactIterative PROC
    PUSH EBP
    MOV EBP, ESP
    PUSH EBX
    PUSH ECX
    
    MOV ECX, [EBP + 8]      ; Get parameter n (loop counter)
    MOV EAX, 1              ; Initialize result to 1
    
    ; Handle edge case: if n <= 1, return 1
    CMP ECX, 1
    JBE IterEnd
    
    ; Loop: multiply result by each number from 2 to n
    MOV EBX, 2              ; Start multiplier at 2
    
IterLoop:
    MUL EBX                 ; EAX = EAX * EBX
    INC EBX                 ; Next multiplier
    CMP EBX, ECX            ; Compare with n
    JBE IterLoop            ; Continue if EBX <= n
    
IterEnd:
    POP ECX
    POP EBX
    POP EBP
    RET 4
FactIterative ENDP

;--------------------------------------------------------------------
main PROC
    ; Display prompt
    MOV EDX, OFFSET prompt
    CALL WriteString
    
    ; Read integer from user
    CALL ReadInt
    
    ; Validate input (0 <= n <= 12)
    CMP EAX, 0
    JL InputError
    CMP EAX, 12
    JG InputError
    
    PUSH EAX                ; Save n for later use
    
    ;=== Calculate and display recursive result ===
    PUSH EAX                ; Push n as parameter
    CALL FactRecursive
    
    ; Save result before I/O
    PUSH EAX
    
    MOV EDX, OFFSET recursiveMsg
    CALL WriteString
    
    POP EAX
    CALL WriteDec
    
    MOV EDX, OFFSET newline
    CALL WriteString
    
    ;=== Calculate and display iterative result ===
    MOV EAX, [ESP]          ; Get n from stack (don't pop yet)
    PUSH EAX
    CALL FactIterative
    
    ; Save result before I/O
    PUSH EAX
    
    MOV EDX, OFFSET iterativeMsg
    CALL WriteString
    
    POP EAX
    CALL WriteDec
    
    MOV EDX, OFFSET newline
    CALL WriteString
    MOV EDX, OFFSET newline
    CALL WriteString
    
    ;=== Performance Testing ===
    ; Display iteration count
    MOV EDX, OFFSET iterations
    CALL WriteString
    MOV EAX, testIterations
    CALL WriteDec
    MOV EDX, OFFSET newline
    CALL WriteString
    
    ;--- Test Recursive Version ---
    CALL GetMSeconds        ; Get start time
    PUSH EAX                ; Save start time
    
    MOV ECX, testIterations
RecTestLoop:
    PUSH ECX                ; Save counter
    MOV EAX, [ESP + 8]      ; Get n from stack
    PUSH EAX                ; Push parameter
    CALL FactRecursive
    POP ECX                 ; Restore counter
    LOOP RecTestLoop
    
    CALL GetMSeconds        ; Get end time
    POP EBX                 ; Get start time
    SUB EAX, EBX            ; Calculate elapsed time
    
    ; Save and display recursive time
    PUSH EAX
    MOV EDX, OFFSET recursiveTime
    CALL WriteString
    POP EAX
    CALL WriteDec
    PUSH EAX                ; Save for comparison
    MOV EDX, OFFSET newline
    CALL WriteString
    
    ;--- Test Iterative Version ---
    CALL GetMSeconds        ; Get start time
    PUSH EAX                ; Save start time
    
    MOV ECX, testIterations
IterTestLoop:
    PUSH ECX                ; Save counter
    MOV EAX, [ESP + 12]     ; Get n from stack (offset adjusted)
    PUSH EAX                ; Push parameter
    CALL FactIterative
    POP ECX                 ; Restore counter
    LOOP IterTestLoop
    
    CALL GetMSeconds        ; Get end time
    POP EBX                 ; Get start time
    SUB EAX, EBX            ; Calculate elapsed time
    
    ; Display iterative time
    PUSH EAX
    MOV EDX, OFFSET iterativeTime
    CALL WriteString
    POP EAX
    CALL WriteDec
    MOV EDX, OFFSET newline
    CALL WriteString
    
    ; Clean up stack
    POP EBX                 ; Remove recursive time
    POP EAX                 ; Remove n
    
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