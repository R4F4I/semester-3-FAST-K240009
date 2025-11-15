; Write a program which contains a procedure named MinMaxArray that displays the minimum
; & maximum values in an array. Pass a size-20 array by reference to this procedure.
INCLUDE Irvine32.inc

.data
    ; Size-20 array of DWORDS (20 * 4 = 80 bytes)
    int_array DWORD 10, -5, 30, 8, 1, 55, 12, -20, 42, 9, 
                  100, 15, 77, 4, 18, 60, -3, 25, 50, 2
    
    ARRAY_SIZE = 20
    
    max_msg     BYTE "Maximum Value: ", 0
    min_msg     BYTE "Minimum Value: ", 0

.code


MinMaxArray PROC
    ; --- Prologue: RA Management & Parameter Consumption ---
    POP ESI             ; Purpose: Temporarily store the outer procedure's Return Address (RA).
    
    ; 1. Load Parameters (Consumed via POP)
    POP EDI             ; EDI = Address of the array (Pushed second in main)
    POP ECX             ; ECX = Array size (Loop counter) (Pushed first in main)
    
    ; 2. Save Volatile Registers (The stack is now clean of parameters)
    PUSH EDI            ; Save EDI, which is used as the array pointer
    PUSH EBX            ; EBX will store Max
    PUSH EDX            ; EDX will store Min

    ; --- Initialization ---
    ; Load the first element into EAX
    MOV EAX, [EDI]
    
    ; Initialize Max (EBX) and Min (EDX) to the first element
    MOV EBX, EAX        ; EBX = Max
    MOV EDX, EAX        ; EDX = Min
    
    ; Advance pointer and decrement count for loop (already processed 1st element)
    ADD EDI, TYPE DWORD ; Move EDI to the second element
    DEC ECX             ; Decrease count by 1
    
    JECXZ MM_DONE       ; Skip loop if array has size 1 or less

; --- Main Loop ---
MM_LOOP:
    ; Load current element into EAX
    MOV EAX, [EDI]
    
    ; Check for new Maximum (EBX)
    CMP EAX, EBX
    JLE CHECK_MIN       ; If EAX <= EBX, skip max update
    MOV EBX, EAX        ; Update Max = EAX
    
CHECK_MIN:
    ; Check for new Minimum (EDX)
    CMP EAX, EDX
    JGE NEXT_ELEMENT    ; If EAX >= EDX, skip min update
    MOV EDX, EAX        ; Update Min = EAX
    
NEXT_ELEMENT:
    ADD EDI, TYPE DWORD ; Move pointer to next element
    LOOP MM_LOOP        ; Decrement ECX and loop if ECX != 0

; --- Display Results (Guaranteed to hold the correct results in EBX/EDX) ---
MM_DONE:
    ; Isolate the Minimum value into ECX to protect it from EDX pointer usage
    MOV ECX, EDX        ; ECX now safely holds the Minimum value (originally in EDX)

    CALL Crlf           ; Newline for formatting
    
    ; Display Maximum Value
    MOV EAX, EBX        ; Move Max value into EAX for WriteInt
    MOV EDX, OFFSET max_msg
    CALL WriteString
    CALL WriteInt
    CALL Crlf

    ; Display Minimum Value
    MOV EAX, ECX        ; Move Min from safe ECX register into EAX for WriteInt
    MOV EDX, OFFSET min_msg
    CALL WriteString
    CALL WriteInt
    CALL Crlf
    
    ; --- Epilogue: Restore Volatile Registers (must reverse PUSH order) ---
    ; Note: The original values of EDX, EBX, EDI are restored here, covering ECX's temporary use.
    POP EDX             ; Restore original EDX, EBX, EDI
    POP EBX              
    POP EDI             
    
    ; --- RA Management & Return ---
    PUSH ESI            ; Purpose: Place the Return Address back on the stack for program integrity.
    RET                 ; Returns to caller. No RET 8 needed as POP consumed the parameters.
MinMaxArray ENDP


main PROC
    ; --- Pass parameters to MinMaxArray ---
    
    ; PUSH 1: Array Size
    PUSH ARRAY_SIZE
    
    ; PUSH 2: Array Address
    PUSH OFFSET int_array
    
    ; Call the procedure
    CALL MinMaxArray    
    
    exit
main ENDP
end main