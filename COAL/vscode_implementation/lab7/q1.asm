; Q1 Write an Assembly program that stores three 8-bit values in registers. Use
; AND, OR, and XOR instructions to clear all odd bits, set all even bits, and then
; toggle all bits. Finally, use the TEST instruction to check whether bit 0 is set in
; the final result and display "Bit 0 is ON" or "Bit 0 is OFF" using conditional
; jumps.




INCLUDE Irvine32.inc


.data


; Define strings to be displayed based on the result.
msgOn  BYTE "Bit 0 is ON", 0
msgOff BYTE "Bit 0 is OFF", 0




.code
main PROC


    mov eax, 0


    mov al, 10100111b
    mov bl, 10100111b
    mov cl, 10100111b


    ; clear all odd bits in al
    and al, 10101010b
    call writeBin    
    call CRLF ; newline


    ; set all even bits
    or al, 10101010b


    call writeBin
    call CRLF ; newline
   
    ; invert/toggle(0->1 , 1->0) ALL BITS
    xor al, 11111111b


    call writeBin
    call CRLF ; newline


    ; TEST whether 1st bit is 0 or 1
    test al, 00000001b


    jz BitIsOff


    ; else bit is on
    mov edx, OFFSET msgOn
    call WriteString


    jmp TheEnd ; else jump to end


BitIsOff:
    mov edx, OFFSET msgOff
    call WriteString




TheEnd:




exit
main ENDP


END main