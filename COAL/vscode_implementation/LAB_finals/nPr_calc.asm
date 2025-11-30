; The Task: Create a program that calculates 
;           the number of Permutations (nPr) using the formula: nPr=(n−r)!n!
;     1. Create a Recursive Procedure named Factorial using INVOKE and PROTO.
;     2. The Factorial procedure must use EBP stack frames.
;     3. In main, ask for n and r, calculate the numerator (n!) and denominator ((n−r)!) separately, and use DIV to find the result


INCLUDE Irvine32.inc

.data

msgN    BYTE "Enter n: ",0
msgR    BYTE "Enter r: ",0
msgRes  BYTE "Result (nPr): ",0
nVal    DWORD ?
rVal    DWORD ?
num     DWORD ?     ; Numerator
denom   DWORD ?     ; Denominator


.code

fact PROC uses ebx, value:DWORD ; during `invoke fact, n` -> n will be pushed to stack, value 

mov eax, value
cmp eax, 0
; call dumpRegs
ja recurse

mov eax, 1
jmp finish

recurse:
dec eax

invoke fact, eax
mov ebx, value
; call writeDec
call crlf
mul ebx ; mul ebx and eax

finish:
ret
fact ENDP

; int fact(int n){
; if (n==0) 
;   return 1;
; return n*fact(n-1);

; }

main PROC

    ; nPr is n!/(n-r)! 

    mov edx, offset msgN
    call writeString
    call readDec
    mov nVal, eax

    mov edx, offset msgR
    call writeString
    call readDec
    mov rVal, eax

    invoke fact, nVal

    ; eax now contains n!
    mov num, eax
    ; num now contains n!

    mov eax, nVal
    sub eax, rVal
    
    mov nVal, eax
    ; nVal now contains n-r

    invoke fact, nVal
    ; eax contains (n-r)!
    xchg num, eax
    div num
    call writeDec
    

    

    exit
main ENDP
end main