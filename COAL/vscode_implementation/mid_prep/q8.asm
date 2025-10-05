TITLE SIGNED INTEGER I/O

INCLUDE Irvine32.inc


.data

prompt BYTE "enter a signed integer: ", 0
res BYTE "The result is: ", 0

.code
main PROC

; prompt
mov edx, offset prompt
call writeString

call Readint    ; eax = n
mov ebx, 5
mul ebx     ; mul the num in eax by num in ebx, 
            ; and moves it to eax, 
            ; for higher num edx stores the higher bits

mov edx, offset res
call writeString
call writedec





exit
main ENDP
end main