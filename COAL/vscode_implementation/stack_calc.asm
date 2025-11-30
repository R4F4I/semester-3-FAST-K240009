INCLUDE Irvine32.inc

.data

wordList WORD 2,3,4,5,6 ; 2 byte / 8 bit array, each element is of size of 2 bytes or 4 hex digits

; like this
;  1 0
; 0002h
;  3 2
; 0003h
;  5 4
; 0004h
;  7 6
; 0005h
;  9 8
; 0006h


.code 
main PROC

xor eax, eax ; clear eax
mov eax, DWORD PTR [wordList+6] ; wordList refers to the first element of wordList, [wordList+n], means go to the nth byte from wordList
; [wordList+2] returns 3
; DWORD PTR type casts [wordList+6], 
; DWORD is 4 bytes, meaning 8 hex digits,
; hence its picks up 0005 AND 0006 and pastes them to eax (which supports DWORD)
call WriteHex

    exit
main ENDP
end main