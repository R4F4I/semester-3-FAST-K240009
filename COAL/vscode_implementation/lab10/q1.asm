; Write a program which contains a procedure named ThreeProd that displays the product of 
; three numeric parameters passed through a stack.
INCLUDE Irvine32.inc

.data

.code

ThreeProd PROC

pop esi
pop eax

pop ebx
IMUL ebx

pop ebx
IMUL ebx

call writeInt
ret
ThreeProd ENDP

main PROC

push 5
push 2
push 3

call ThreeProd

exit
main ENDP
end main