TITLE MyFirstProgram (file1.asm)
INCLUDE irvine32.inc
.code
main PROC
mov eax, 10h
mov ebx, 25h
call DumpRegs
exit
main ENDP
END main