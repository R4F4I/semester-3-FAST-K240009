;Write a program which contains a procedure named BubbleSort that sorts an array which is
;passed through a stack using indirect addressing.
INCLUDE Irvine32.inc

.data
    array       DWORD 50, -20, 80, 10, 40, 5, 100, -2
    ARRAY_SIZE = ($-array) / TYPE array ; Calculate size automatically

    msg_before  BYTE "Before sorting: ", 0
    msg_after   BYTE "After sorting:  ", 0
    space_char  BYTE "  ", 0

.code


BubbleSort PROC
    ; Purpose: Establish a reliable stack frame pointer.
    PUSH EBP
    MOV EBP, ESP
    ; Save registers used by this procedure
    PUSH EAX
    PUSH EBX
    PUSH ECX
    PUSH ESI

    ; --- Get Parameters ---
    MOV ECX, [EBP+12]   ; Get array size (n) from [EBP+12]
    DEC ECX             ; Outer loop count (n-1)
    JECXZ BS_DONE       ; If size < 1, exit

; --- Outer Loop (L1) ---
; Controls the number of passes (n-1)
L1_OUTER:
    PUSH ECX            ; Save outer loop counter (k)
    MOV ESI, [EBP+8]    ; FIX: Get array address from [EBP+8] (Reset for inner loop)

    ; --- Inner Loop (L2) ---
    ; Compares and swaps adjacent elements
    ; Inner loop runs k times, where k decreases
L2_INNER:
    ; Compare [ESI] with [ESI+4] (array[i] with array[i+1])
    MOV EAX, [ESI]
    MOV EBX, [ESI + TYPE DWORD] ; Use EBX for array[i+1]
    
    CMP EAX, EBX
    JLE L2_NO_SWAP      ; If EAX <= EBX, no swap needed

    ; Swap elements
    MOV [ESI + TYPE DWORD], EAX ; array[i+1] = EAX
    MOV [ESI], EBX              ; array[i] = EBX

L2_NO_SWAP:
    ADD ESI, TYPE DWORD         ; Move pointer to next element
    LOOP L2_INNER               ; Uses ECX (which was k)

    POP ECX             ; Restore outer loop counter (k)
    
    LOOP L1_OUTER       ; Uses ECX (which was k)

BS_DONE:
    ; Purpose: Restore saved registers
    POP ESI
    POP ECX
    POP EBX
    POP EAX
    ; Purpose: De-allocate and restore caller's frame.
    POP EBP
    RET 8               ; Clean up 2 parameters (address + size)
BubbleSort ENDP


main PROC
    ; --- Display "Before" ---
    MOV EDX, OFFSET msg_before
    CALL WriteString

    ; --- NEW: Inline Display Loop (Replaces CALL DisplayArray) ---
    ; Purpose: Use PUSHAD/POPAD to save ALL registers (EAX, ECX, EDX, etc.)
    ; This protects the loop counter (ECX) from I/O calls.
    PUSHAD
    
    MOV ESI, OFFSET array
    MOV ECX, ARRAY_SIZE
    JECXZ PRINT_DONE_1
    
PRINT_LOOP_1:
    MOV EAX, [ESI]
    CALL WriteInt
    
    MOV EDX, OFFSET space_char
    CALL WriteString
    
    ADD ESI, TYPE DWORD
    LOOP PRINT_LOOP_1

PRINT_DONE_1:
    CALL Crlf
    POPAD               ; Restore ALL registers

    ; --- Call BubbleSort ---
    PUSH ARRAY_SIZE
    PUSH OFFSET array
    CALL BubbleSort

    ; --- Display "After" ---
    MOV EDX, OFFSET msg_after
    CALL WriteString
    
    ; --- NEW: Inline Display Loop 2 (Replaces CALL DisplayArray) ---
    PUSHAD
    
    MOV ESI, OFFSET array
    MOV ECX, ARRAY_SIZE
    JECXZ PRINT_DONE_2
    
PRINT_LOOP_2:
    MOV EAX, [ESI]
    CALL WriteInt
    
    MOV EDX, OFFSET space_char
    CALL WriteString
    
    ADD ESI, TYPE DWORD
    LOOP PRINT_LOOP_2

PRINT_DONE_2:
    CALL Crlf
    POPAD
    
    exit
main ENDP
end main