.386
.model flat, c         ; Use the flat memory model and C calling convention
INCLUDE Irvine32.inc   ; Include the Irvine32 library for I/O functions

.data
    resultMsg BYTE "The product calculated by Assembly is: ", 0
    
.code

; Parameters (passed on stack using C calling convention):
; [EBP+16] -> First parameter (num1)
; [EBP+12] -> Second parameter (num2)
; [EBP+8]  -> Third parameter (num3)
ThreeProd PROC
    ; Standard procedure prologue: save base pointer and set up new frame
    push ebp
    mov ebp, esp

    ; Display the introductory message
    mov edx, OFFSET resultMsg
    call WriteString
    
    ; Calculation: (num1 * num2) * num3     
    ; 1. Load the first parameter (num1) into EAX
    mov eax, [ebp+16]       ; EAX = num1

    ; 2. Multiply EAX by num2
    imul [ebp+12]           ; EAX = EAX * num2 (Result in EAX, assuming no overflow beyond 32 bits)

    ; 3. Multiply the current result (in EAX) by num3
    imul [ebp+8]            ; EAX = (num1 * num2) * num3. Final 32-bit product is in EAX.

    ; Output the Result     
    ; EAX already holds the final product to display
    call WriteDec
    call Crlf
    
    ; Standard procedure epilogue: restore base pointer and return
    pop ebp
    ret                     ; Return to caller (C++ will clean up the stack)
ThreeProd ENDP

END