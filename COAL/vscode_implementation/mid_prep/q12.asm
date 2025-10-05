INCLUDE Irvine32.inc

.data

msg1 byte "enter input: ", 0
msg2 byte "input must be positive ", 0

.code
main PROC


input:
mov edx, offset msg1
call writestring

call ReadInt

cmp eax, 1
jl isZero


; now try to sum all num from 1 to N
mov ecx, eax
mov eax, 0
loopStart:
    add eax, ecx
loop loopStart

call writeDec
jmp L_exit

isZero:
mov edx, offset msg2
call writestring
call crlf
jmp input


L_exit:

exit
main ENDP
end main