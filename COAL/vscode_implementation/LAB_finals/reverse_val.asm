INCLUDE Irvine32.inc


.data
val WORD 5678h
byteSize BYTE 4

.code
main PROC

    xor eax, eax
    mov ax, val
    xchg al, ah ; swap upper 2 and lower 2 -> 7856
    
    
    xor ecx, ecx ; rotate both al and ah to get 87 65
    mov cl, 4
    rol al, cl
    rol ah, cl
    call dumpRegs


    exit
main ENDP
end main