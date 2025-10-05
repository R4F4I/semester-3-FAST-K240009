INCLUDE Irvine32.inc

.data

A SDWORD 50
B SDWORD 10
E SDWORD 5
D SDWORD 2


.code
main PROC

mov eax, A
sub eax, B

add eax, E

mov ebx, D
add ebx, 5

sub eax, ebx

call writedec


exit

main ENDP
end main