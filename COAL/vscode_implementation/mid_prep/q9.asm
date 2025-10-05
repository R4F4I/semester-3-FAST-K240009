INCLUDE Irvine32.inc

.data

num1 DWORD 50
num2 DWORD 100

msg1 byte "num1 > num2", 0
msg2 byte "num1 < num2", 0

.code
main PROC

mov eax, num1
mov ebx, num2

cmp eax, ebx
jge L1_GreaterEqual

jmp L2_Lesser

L1_GreaterEqual:
mov edx, offset msg1
call writeString


; this is an else statement 
; hence must be skipped if not jumped to
jmp skip
L2_Lesser:
mov edx, offset msg2
call writeString


skip:

exit
main ENDP
end main