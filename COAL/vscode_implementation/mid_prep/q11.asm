INCLUDE Irvine32.inc


.data

char byte "*"

.code
main PROC

mov ecx, 5
mov ebx, 0 ; for the conditional loop outside
mov edx, offset char

LOOP1:

    LOOP2:
        mov al, char
        call writechar

    LOOP LOOP2

    call crlf

inc ebx
cmp ebx, 5
call dumpRegs
jl LOOP1


exit
main ENDP
end main