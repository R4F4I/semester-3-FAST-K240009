; =========================================================================
; 3rd-Degree Polynomial Using ONLY Stack (Flexible Version)
;
; Formula: f(x) = 3x^3 + 2x^2 - 5x + 7
; Method:  Horner's Method
;          f(x) = ( ( (3*x) + 2 ) * x - 5 ) * x + 7
;
; Requirement: Change 'x_val' in .data to test different inputs.
; =========================================================================

.386
.model flat, stdcall
.stack 4096
INCLUDE Irvine32.inc

; -------------------------------------------------------------------------
; Data Segment
; -------------------------------------------------------------------------
.data
    ; --- Input Value (CHANGE THIS TO TEST) ---
    x_val   DWORD   4   ; Test with x = 3. Try 4, 5, 6, etc.

    ; --- Coefficients ---
    c3      DWORD   3
    c2      DWORD   2
    c1      DWORD  -5
    c0      DWORD   7
    
    ; --- Output Strings ---
    msgX    BYTE    "Enter x: ", 0
    msgPoly BYTE    "Polynomial: 3x^3 + 2x^2 - 5x + 7", 0Dh, 0Ah, 0
    msgRes  BYTE    "Result: ", 0
    
    ; --- Stack Trace Strings ---
    msgPush BYTE    "Stack trace:", 0Dh, 0Ah, 0
    msgCoef BYTE    "Pushed coefficients: 3, 2, -5, 7", 0Dh, 0Ah, 0

; -------------------------------------------------------------------------
; Code Segment
; -------------------------------------------------------------------------
.code
main PROC
    ; --- 1. Display Headers ---
    MOV EDX, OFFSET msgX
    CALL WriteString
    MOV EAX, x_val      ; Load the input x
    CALL WriteInt       ; Print the input x
    CALL Crlf
    
    MOV EDX, OFFSET msgPoly
    CALL WriteString

    ; --- 2. Print Stack Trace Info ---
    MOV EDX, OFFSET msgPush
    CALL WriteString
    MOV EDX, OFFSET msgCoef
    CALL WriteString

    ; --- 3. Evaluate Polynomial using Horner's Method & Stack ---
    ; We are calculating: ( ( (c3*x) + c2 ) * x + c1 ) * x + c0
    ; The stack will only ever hold one or two intermediate values.

    ; PUSH c3
    PUSH c3             ; STACK: [3]

    ; ... * x
    PUSH x_val          ; STACK: [x, 3]
    POP EAX             ; EAX = x
    POP EBX             ; EBX = 3
    IMUL EAX, EBX       ; EAX = 3*x
    PUSH EAX            ; STACK: [3x]

    ; ... + c2
    PUSH c2             ; STACK: [2, 3x]
    POP EAX             ; EAX = 2
    POP EBX             ; EBX = 3x
    ADD EAX, EBX        ; EAX = 3x + 2
    PUSH EAX            ; STACK: [3x + 2]

    ; ... * x
    PUSH x_val          ; STACK: [x, 3x+2]
    POP EAX             ; EAX = x
    POP EBX             ; EBX = 3x+2
    IMUL EAX, EBX       ; EAX = (3x+2) * x
    PUSH EAX            ; STACK: [3x^2 + 2x]

    ; ... + c1
    PUSH c1             ; STACK: [-5, 3x^2+2x]
    POP EAX             ; EAX = -5
    POP EBX             ; EBX = 3x^2+2x
    ADD EAX, EBX        ; EAX = 3x^2 + 2x - 5
    PUSH EAX            ; STACK: [3x^2 + 2x - 5]

    ; ... * x
    PUSH x_val          ; STACK: [x, 3x^2+2x-5]
    POP EAX             ; EAX = x
    POP EBX             ; EBX = 3x^2+2x-5
    IMUL EAX, EBX       ; EAX = (3x^2+2x-5) * x
    PUSH EAX            ; STACK: [3x^3 + 2x^2 - 5x]

    ; ... + c0
    PUSH c0             ; STACK: [7, 3x^3+...]
    POP EAX             ; EAX = 7
    POP EBX             ; EBX = 3x^3+...
    ADD EAX, EBX        ; EAX = 3x^3 + 2x^2 - 5x + 7
    PUSH EAX            ; STACK: [Final Result]

    ; --- 4. Display Final Result ---
    MOV EDX, OFFSET msgRes
    CALL WriteString
    
    POP EAX             ; EAX = Final Result (Get it from the stack)
    CALL WriteInt       ; Display the final result
    CALL Crlf

    INVOKE ExitProcess, 0
main ENDP
END main