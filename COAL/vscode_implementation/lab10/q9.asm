; Write a program which contains a procedure named TakeInput which takes input numbers
; from user and call a procedure named Armstrong which checks either a number is an Armstrong
; number or not and display the answer on console by calling anotherfunction Display. (Also show
; ESP values during nested function calls)
INCLUDE Irvine32.inc
.386 ; Enable 32-bit instruction set

.data
    msg_yes     BYTE "YES, it is an Armstrong number.", 0
    msg_no      BYTE "NO, it is not an Armstrong number.", 0

    ; --- New Input Method ---
    number_to_check DWORD 153
    digit_array     DWORD 1, 5, 3
    num_digits      = ($ - digit_array) / TYPE digit_array ; "Check the arr size"

.code

;-----------------------------------------------------------
; Power PROC
; Calculates base^exponent (x^y)
; Parameters:
;   [EBP+12] = exponent (y)
;   [EBP+8]  = base (x)
; Returns: Result in EAX
;-----------------------------------------------------------
Power PROC
    ; Purpose: Establish a reliable stack frame pointer.
    PUSH EBP
    MOV EBP, ESP
    PUSH EBX            ; Save registers
    PUSH ECX

    MOV EAX, 1          ; result = 1
    MOV EBX, [EBP+8]    ; EBX = base (x)
    MOV ECX, [EBP+12]   ; ECX = exponent (y)
    
    CMP ECX, 0          ; If exponent is 0, result is 1
    JE POWER_DONE

POWER_LOOP:
    IMUL EAX, EBX       ; result = result * base
    LOOP POWER_LOOP
    
POWER_DONE:
    POP ECX             ; Restore registers
    POP EBX
    ; Purpose: De-allocate and restore caller's frame.
    POP EBP
    RET 8               ; Clean up 2 parameters (8 bytes)
Power ENDP

Display PROC
    ; Purpose: Establish a reliable stack frame pointer.
    PUSH EBP
    MOV EBP, ESP
    PUSH EAX
    PUSH EDX
    
    CALL Crlf
    MOV EAX, [EBP+8]    ; Get the flag
    CMP EAX, 1
    JE IS_YES
    
    ; --- NO Case ---
    MOV EDX, OFFSET msg_no
    JMP DISPLAY_MSG
    
IS_YES:
    ; --- YES Case ---
    MOV EDX, OFFSET msg_yes
    
DISPLAY_MSG:
    CALL WriteString
    CALL Crlf
    
    POP EDX
    POP EAX
    ; Purpose: De-allocate and restore caller's frame.
    POP EBP
    RET 4               ; Clean up 1 parameter (4 bytes)
Display ENDP

Armstrong PROC
    LOCAL sum:DWORD     ; Local variable
    
    ; Purpose: Establish stack frame, save registers, allocate local vars
    PUSH EBP
    MOV EBP, ESP
    SUB ESP, 4          ; Allocate 4 bytes (1 DWORD) for sum
    PUSH ESI            ; Save registers
    PUSH EBX
    PUSH ECX
    PUSH EDX
    
    ; Local var location:
    ; sum = [EBP-4]
    
    MOV ESI, OFFSET digit_array     ; ESI = array pointer
    MOV ECX, num_digits             ; ECX = loop counter
    MOV DWORD PTR [EBP-4], 0        ; sum = 0

    ; --- 2. Calculate Sum of Powers (Replaces DIV loop) ---
SUM_LOOP:
    CMP ECX, 0
    JE SUM_DONE         ; If count = 0, stop
    
    MOV EDX, [ESI]      ; EDX = current digit from array
    
    ; --- 2a. Call Power(digit, num_digits) (Nested Call) ---
    PUSH num_digits     ; ESP decreases by 4 (Param 2: exponent)
    PUSH EDX            ; ESP decreases by 4 (Param 1: base/digit)
    CALL Power          ; ESP decreases by 4 (Pushes RA)
    ADD ESP, 8          ; (Power's RET 8 is simulated by ADD)
    
    ADD DWORD PTR [EBP-4], EAX    ; Add EAX (power_result) to sum
    
    ADD ESI, TYPE DWORD ; Move array pointer to next digit
    LOOP SUM_LOOP
    
SUM_DONE:
    ; --- 3. Compare sum with original_n ---
    MOV EAX, DWORD PTR [EBP-4]    ; EAX = sum
    MOV EBX, number_to_check
    CMP EAX, EBX        ; Compare sum with number_to_check
    JNE NOT_ARMSTRONG
    
    MOV EAX, 1          ; YES, it is Armstrong
    JMP ARM_DONE
    
NOT_ARMSTRONG:
    MOV EAX, 0          ; NO, it is not
    
ARM_DONE:
    POP EDX             ; Restore registers
    POP ECX
    POP EBX
    POP ESI
    MOV ESP, EBP        ; De-allocate local variables
    POP EBP             ; Restore caller's EBP
    RET                 ; No parameters to clean up
Armstrong ENDP

;-----------------------------------------------------------
main PROC
    ; --- Call Armstrong (Nested) ---
    CALL Armstrong      ; ESP decreases by 4 (Pushes RA)
                        ; Result (0 or 1) is now in EAX
                        
    ; --- Call Display (Nested) ---
    PUSH EAX            ; ESP decreases by 4 (Param: 0 or 1)
    CALL Display        ; ESP decreases by 4 (Pushes RA)
    ADD ESP, 4          ; (Display's RET 4 is simulated by ADD)
    
    exit
main ENDP
end main