INCLUDE Irvine32.inc

.data

msg_welcome BYTE "welcome to COAL", 0
msg_end BYTE "program ended", 0

time_delay dword 2000 ; for 2000 milliseconds

.code
main PROC

CALL Clrscr

mov edx, offset msg_welcome
call writeString

mov eax, time_delay
call delay

mov edx, offset msg_end
call crlf
call writeString


exit
main ENDP

END main