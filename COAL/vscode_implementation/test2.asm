INCLUDE Irvine32.inc

.data

msg_welcome BYTE "welcome to COAL", 0 ; length is 16 (including the null terminator) 16d=10h
array_word word 5 dup (?),1,2,3  ; a word is 2 bytes

.code
main PROC

mov eax, SIZEOF array_word
mov ecx, lengthof msg_welcome

call dumpregs


exit
main ENDP

END main