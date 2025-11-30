; The Task: Write a program that reads a string from the user. 
; For every character in the string, 
; perform the following encryption based on the Parity Flag (PF):
;     Check Parity: If the character has Even Parity, Rotate it Left (ROL) by 2 bits.
;     If the character has Odd Parity, Rotate it Right (ROR) by 2 bits.
;     Key Mask: After rotation, XOR the result with a key 0Fh.
;     Store the result in a new buffer and display the encrypted string in Hexadecimal.

INCLUDE Irvine32.inc

.data

prompt BYTE "enter text to scramble: ",0
buffer BYTE 51 DUP (0)
cipher BYTE 51 DUP (0)
byteCount DWORD ?


.code
main PROC

; display prompt
mov edx, offset prompt
call writeString

; input val
mov edx, offset buffer
mov ecx, sizeof buffer
call ReadString ; user input moved to edx, char count in eax
mov byteCount, eax ; user input count stored in byteCount
call dumpRegs

mov ecx, byteCount
mov esi, 0 ; clearing esi, it will used for offsets []
call dumpRegs

encryptionLoop:
    mov al, buffer[esi] ; load character

    test al, al ; set parity flag, by checking whether the char has even or odd bits
    call dumpRegs
    jp evenParity ; jump if PF=1

    oddParity:
        ror al, 2 ; rotated by 2
        jmp applyMask
    evenParity:
        rol al, 2 

    applyMask:
        xor al, 0Fh ; 0000 1111 xor -> all ax bits flipped
        mov cipher[esi], al ; store in new output

    inc esi
loop encryptionLoop

mov esi, 0
mov ecx, byteCount

printHex:
    movzx eax, cipher[esi]
    call WriteHex
    mov al, ' '
    call WriteChar
    inc esi
    loop printHex

    call crlf



    exit
main ENDP
end main