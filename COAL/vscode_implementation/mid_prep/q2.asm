INCLUDE Irvine32.inc

.data


.code
main PROC

mov eax, 1010110b
add eax, 1a0h
sub eax, 20

call writedec


exit
main ENDP

END main