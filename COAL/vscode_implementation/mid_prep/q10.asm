INCLUDE Irvine32.inc

.data


.code
main PROC


; sum of the first 10 +ve int

mov ecx, 10
mov eax, 0

loopStart:

    add eax, ecx


LOOP loopStart

call writedec

exit
main ENDP
end main