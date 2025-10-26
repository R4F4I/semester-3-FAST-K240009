INCLUDE Irvine32.inc

; -------------------------------------------------------------------------
; Data Segment
; -------------------------------------------------------------------------
.data
    ; Input Values
    A   DWORD   5
    B   DWORD   3
    E   DWORD   4
    D   DWORD   2
    
    ; Output Strings
    msgVals BYTE "A=5, B=3, C=4, D=2", 0Dh, 0Ah, 0
    msg1    BYTE "Step1 (A+B): ", 0
    msg2    BYTE "Step2 ((A+B)*C): ", 0
    msg3    BYTE "Final ((A+B)*C)-D: ", 0

; -------------------------------------------------------------------------
; Code Segment
; -------------------------------------------------------------------------
.code

; -------------------------------------------------------------------------
; Procedure 1: Adds A and B
; Returns: Result (A+B) in EAX
; -------------------------------------------------------------------------
AddProc PROC
    MOV EAX, A      ; EAX = A (5)
    ADD EAX, B      ; EAX = EAX + B (5 + 3 = 8)
    RET             ; Return with result in EAX
AddProc ENDP

; -------------------------------------------------------------------------
; Procedure 2: Multiplies EAX by C
; Receives: (A+B) in EAX
; Returns: Result ((A+B)*C) in EAX
; -------------------------------------------------------------------------
MulProc PROC
    ; EAX is already 8 from AddProc
    IMUL EAX, E     ; EAX = EAX * E (8 * 4 = 32)
    RET             ; Return with result in EAX
MulProc ENDP

; -------------------------------------------------------------------------
; Procedure 3: Subtracts D from EAX
; Receives: ((A+B)*C) in EAX
; Returns: Final Result in EAX
; -------------------------------------------------------------------------
SubProc PROC
    ; EAX is already 32 from MulProc
    SUB EAX, D      ; EAX = EAX - D (32 - 2 = 30)
    RET             ; Return with result in EAX
SubProc ENDP


; -------------------------------------------------------------------------
; Main Program
; -------------------------------------------------------------------------
main PROC
    ; Display initial values
    MOV EDX, OFFSET msgVals
    CALL WriteString

    ; --- Step 1 ---
    CALL AddProc
    ; EAX now holds 8
    
    MOV EDX, OFFSET msg1
    CALL WriteString
    CALL WriteInt       ; Prints the value in EAX (8)
    CALL Crlf

    ; --- Step 2 ---
    ; EAX (8) is the implicit input for MulProc
    CALL MulProc
    ; EAX now holds 32

    MOV EDX, OFFSET msg2
    CALL WriteString
    CALL WriteInt       ; Prints the value in EAX (32)
    CALL Crlf

    ; --- Step 3 ---
    ; EAX (32) is the implicit input for SubProc
    CALL SubProc
    ; EAX now holds 30

    MOV EDX, OFFSET msg3
    CALL WriteString
    CALL WriteInt       ; Prints the value in EAX (30)
    CALL Crlf
    
    INVOKE ExitProcess, 0
main ENDP

END main