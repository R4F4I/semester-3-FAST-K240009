TITLE   Ultimate Debugging Counter

INCLUDE Irvine32.inc

.data
counter DWORD 0

.code
main PROC
    call Clrscr

main_loop:
    ; 1. Move cursor to the top-left corner
    mov  edx, 0
    call Gotoxy

    ; 2. Display the current value of our counter
    mov  eax, counter
    call WriteDec          ; WriteDec is an Irvine32 function that prints a number

    ; 3. Wait for half a second so we can clearly see the update
    mov  eax, 500
    call Sleep

    ; 4. Increment the counter for the next loop
    inc  counter

    ; 5. Repeat
    jmp  main_loop

    exit
main ENDP

END main