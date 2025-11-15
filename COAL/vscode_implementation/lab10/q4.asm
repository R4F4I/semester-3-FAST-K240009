;Write a program which contains a procedure named LocalSquare . The procedure must
;declare a local variable. Initialize this variable by taking an input value from the user and then
;display its square. Use ENTER & LEAVE instructions to allocate and de-allocate the local variable.
INCLUDE Irvine32.inc

.data
    prompt_msg      BYTE "Enter a number to square: ", 0
    result_msg      BYTE "The square is: ", 0
    
    ; Define symbolic constant for local variable offset
    LOCAL_VAR_SIZE = 4 ; 4 bytes for a single DWORD

.code

;-----------------------------------------------------------
; LocalSquare PROC
; Declares a local DWORD variable, takes input, calculates the square, 
; and displays the result. Uses ENTER/LEAVE for stack management.
;-----------------------------------------------------------
LocalSquare PROC
    ; Purpose: Establish the stack frame and allocate 4 bytes for local storage.
    ENTER LOCAL_VAR_SIZE, 0 
    ; EBP is set up, and ESP is moved down by 4 bytes.
    ; Local variable is located at [EBP - 4].

    ; --- Input Phase ---
    MOV EDX, OFFSET prompt_msg
    CALL WriteString
    CALL ReadInt        ; Input value is now in EAX

    ; --- Store Input Locally ---
    ; Purpose: Store the user input into the local variable space.
    MOV [EBP - 4], EAX  ; Store EAX (input) into the local variable

    ; --- Calculation Phase ---
    ; Purpose: Retrieve the local variable and square it.
    MOV EAX, [EBP - 4]  ; Get the input value back into EAX
    IMUL EAX            ; Square the value (EAX * EAX). Result remains in EAX.

    ; --- Display Phase ---
    CALL Crlf
    MOV EDX, OFFSET result_msg
    CALL WriteString
    CALL WriteInt

    ; Purpose: De-allocate local variables and restore the Base Pointer (EBP).
    LEAVE               
    ; Equivalent to: MOV ESP, EBP; POP EBP

    RET
LocalSquare ENDP


main PROC
    CALL LocalSquare

    exit
main ENDP
end main