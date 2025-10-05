INCLUDE Irvine32.inc

.data

scores DWORD 100, 95, 80, 75


.code
main PROC

mov eax, 0
mov ebx, 0


mov esi, offset scores
; mov eax, [esi + 3] ; elements are 0-indexed, for 3rd element [esi +2*(sizeof DWORD)]
mov eax, [esi + 2*(SIZEOF DWORD)]
; call writedec
mov ebx, [esi]

call dumpregs




exit
main ENDP
end main


