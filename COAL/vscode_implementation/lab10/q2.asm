; Write a program which contains a procedure named TakeInput which takes input numbers
; from user and call a procedure named GCD which calculates their GCD and display the answer
; on console by calling another function Display. (Also show ESP values during nested function
; calls)
INCLUDE Irvine32.inc 

.data

p1 byte "enter A: ",0
p2 byte "enter B: ",0
res byte "res: ",0

.code




;;;;;;;;;;;;;;;;;;;
Display proc

mov edx, OFFSET res
call writeString

call writeInt
call crlf


ret
Display endp

;;;;;;;;;;;;;;;;;;;
GCD proc
pop esi ; the program also uses the stack to track procedures, when GCD is called its parent proc's return address is also pushed, we will preserve this value to maintain the code order integrity

pop ebx ; save B to ebx
pop eax ; save A


GCD_loop:

cmp ebx,0 
je GCD_done

mov edx, 0
div ebx ; divided by eax, eax = a /b, edx = a%b, 

mov eax, ebx ; a = b
mov ebx, edx ; b = a % b
jmp GCD_loop

GCD_done:
; val is in eax


push esi ; restore the outer procedure RA back from esi
ret
GCD endp


;;;;;;;;;;;;;;;;;;;
TakeInput proc

mov edx, OFFSET p1
call writeString
call readInt
push eax

mov edx, OFFSET p2
call writeString
call readInt
push eax

call GCD
call Display

ret
TakeInput endp


;;;;;;;;;;;;;;;;;;
main PROC

call TakeInput

exit
main ENDP
end main

