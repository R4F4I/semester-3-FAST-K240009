.386
.model flat, c         ; Use the flat memory model and C calling convention
INCLUDE Irvine32.inc   ; Include the Irvine32 library

.data
    resultMsg BYTE "The Greatest Common Divisor is: ", 0

.code

GCD PROC
    ; Standard procedure prologue
    push ebp
    mov ebp, esp
    
    push ebx
    push ecx
    push edx

    
    mov eax, [ebp+12]       ; EAX = A (Dividend)
    mov ebx, [ebp+8]        ; EBX = B (Divisor)
    
    
GCD_LOOP:
    ; Check if B is zero (GCD is the last non-zero remainder, which is currently A)
    cmp ebx, 0
    je  GCD_DONE            ; If EBX (B) == 0, jump to GCD_DONE
    
    ; Perform the step: A = B, B = A % B

    ; Save the current value of A (EAX) to ECX (our temporary storage)
    mov ecx, eax            ; ECX = old A

    ; Set up the division: A / B
    ; EAX = Dividend (A), EBX = Divisor (B)
    mov edx, 0              ; Clear EDX (required for 32-bit division)
    idiv ebx                ; EAX = Quotient (A/B), EDX = Remainder (A % B)

    ; New value assignments:
    mov eax, ebx            ; EAX (new A) = old B (from EBX)
    mov ebx, edx            ; EBX (new B) = old Remainder (from EDX)

    jmp GCD_LOOP            ; Loop again

GCD_DONE:
    ; At this point, EAX holds the GCD result (the last non-zero value of A).
    
    ; Display the introductory message
    mov edx, OFFSET resultMsg
    call WriteString
    
    ; EAX already holds the value to display
    call WriteDec           ; Display the 32-bit signed integer in EAX
    call Crlf               ; Newline for formatting

    ; Restore caller-saved registers
    pop edx
    pop ecx
    pop ebx

    ; Restore stack frame and return
    pop ebp
    ret                     ; Return to caller (C++ cleans up the stack)
GCD ENDP

END