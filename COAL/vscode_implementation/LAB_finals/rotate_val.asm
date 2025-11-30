; rotate a number its length times 5678h -> 5678h
INCLUDE Irvine32.inc

.data

val WORD 5678h
byteSize BYTE 4


.code 
main PROC

    xor eax, eax ; clear eax


    ; rotate this value 4 times
    ; first get the length of this value

    movzx eax, val 
    xor ebx, ebx
    mov ebx, 10
    mov ecx, 0
    start:
        xor edx, edx ;clear edx val from div
        
        div ebx ; divide eax by 10
        
        inc ecx

        cmp eax, 0
        jne start
    endCount:

    dec ecx
    

    ; length of val in ecx
    xor eax, eax
    movzx eax, val ; due to val being WORD

    ; since the rotation is a bit wise operation to move the entire hex digit mul 4
    mov esi, eax
    mov eax, ecx
    mul byteSize
    mov ecx, eax 
    mov eax, esi

    ROL ax, cl ; rotate ax, cx times
    call dumpRegs


; call WriteHex

exit
main ENDP
end main