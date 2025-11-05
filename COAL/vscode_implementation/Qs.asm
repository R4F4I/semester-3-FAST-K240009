INCLUDE Irvine32.inc

.data
    
    num1    DWORD 1
    num2    DWORD 2
    num3    DWORD 3
    num4    DWORD 2
    result  DWORD 0

.code
main PROC
    ;== if(!(num1>num2)|| !(num3==num4))
; if (num1 > num2 && num3 != num4) 
;   result = num1 + num3;
; else if (num2 == num4)
;   result = num2 - num1;
; else
;   result = 0;

    mov eax,    [num1]
    cmp eax,    [num2]

    jle         _else_if

    mov edx,    0
    mov edx,    [num3]
    cmp edx,    [num4]

    je          _else            ; if block will also be skipped if num3==num4

; if block
    mov eax,    [num1]
    add eax,    [num3]
    mov [result], eax
    jmp _end_if




_else_if:

    mov eax, num2
    cmp eax, num4
    jne _else

    
    mov eax,    [num2]
    sub eax,    [num1]
    mov [result], eax

    jmp _end_if


_else:

    mov [result], 0

_end_if:

    mov eax, [result]
    call writeInt
    call crlf

    exit
main ENDP
END main