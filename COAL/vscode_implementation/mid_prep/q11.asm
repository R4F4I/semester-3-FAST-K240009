INCLUDE Irvine32.inc
.data

char byte "*"

.code
main PROC

mov ebx, 1 ; for the conditional loop outside
; mov edx, offset char

LOOP1:
    ; reassign ecx after every inner loop is done
    mov ecx, 5 

    LOOP2:
        mov al, char
        call writechar

    LOOP LOOP2

    call crlf

inc ebx
cmp ebx, 5
jng LOOP1


exit
main ENDP
end main