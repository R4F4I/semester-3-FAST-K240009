INCLUDE Irvine32.inc

.code
main PROC
    mov eax, 10000h
    add eax, 40000h
    sub eax, 20000h

    ; Display the final register values for debugging.
    call DumpRegs
    
    ; Exit the program.
    exit
main ENDP
END main

