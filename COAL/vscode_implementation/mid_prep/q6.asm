INCLUDE Irvine32.inc


.data

.code 

main PROC

mov eax, 0

mov al, 90h
call dumpregs
add al, 70h

call dumpregs

; 90h+70h = 100h, al has capacity of 8bits-> 2 hex digits
; meaning, 100h -> 0 = ZF, CF

exit

main ENDP
end main