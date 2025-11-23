INCLUDE Irvine32.inc
.data
	hour DWORD ?
	min DWORD ?
	sec DWORD ?

	time SystemTime <>

	tens DWORD ?
	ones DWORD ?

	tensAddr DWORD ?
	onesAddr DWORD ?

	n0 BYTE "     000000000       ",0
		BYTE "   00:::::::::00     ",0
		BYTE " 00:::::::::::::00   ",0
		BYTE "0:::::::000:::::::0  ",0
		BYTE "0::::::0   0::::::0  ",0
		BYTE "0:::::0     0:::::0  ",0
		BYTE "0:::::0     0:::::0  ",0
		BYTE "0:::::0     0:::::0  ",0
		BYTE "0:::::0     0:::::0  ",0
		BYTE "0:::::0     0:::::0  ",0
		BYTE "0::::::0   0::::::0  ",0
		BYTE "0:::::::000:::::::0  ",0
		BYTE " 00:::::::::::::00   ",0
		BYTE "   00:::::::::00     ",0
		BYTE "     000000000       ",0

	n1  BYTE "        111111       ",0
		BYTE "       1::::::1      ",0
		BYTE "      1:::::::1      ",0
		BYTE "      111:::::1      ",0
		BYTE "        1::::1       ",0
		BYTE "        1::::1       ",0
		BYTE "        1::::1       ",0
		BYTE "        1::::1       ",0
		BYTE "        1::::1       ",0
		BYTE "        1::::1       ",0
		BYTE "        1::::1       ",0
		BYTE "        1::::1       ",0
		BYTE "     111::::::111    ",0
		BYTE "     1::::::::::1    ",0
		BYTE "     111111111111    ",0

	n2  BYTE " 222222222222222     ",0
		BYTE "2:::::::::::::::22   ",0
		BYTE "2::::::222222:::::2  ",0
		BYTE "2222222     2:::::2  ",0
		BYTE "            2:::::2  ",0
		BYTE "            2:::::2  ",0
		BYTE "         2222::::2   ",0
		BYTE "    22222::::::22    ",0
		BYTE "  22::::::::222      ",0
		BYTE " 2:::::22222         ",0
		BYTE "2:::::2              ",0
		BYTE "2:::::2              ",0
		BYTE "2:::::2       222222 ",0
		BYTE "2::::::2222222:::::2 ",0
		BYTE "22222222222222222222 ",0

	n3  BYTE " 333333333333333     ",0
		BYTE "3:::::::::::::::33   ",0
		BYTE "3::::::33333::::::3  ",0
		BYTE "3333333     3:::::3  ",0
		BYTE "            3:::::3  ",0
		BYTE "            3:::::3  ",0
		BYTE "    33333333:::::3   ",0
		BYTE "    3:::::::::::3    ",0
		BYTE "    33333333:::::3   ",0
		BYTE "            3:::::3  ",0
		BYTE "            3:::::3  ",0
		BYTE "3333333     3:::::3  ",0
		BYTE "3::::::33333::::::3  ",0
		BYTE "3:::::::::::::::33   ",0
		BYTE " 333333333333333     ",0

	n4  BYTE "       444444444     ",0
		BYTE "      4::::::::4     ",0
		BYTE "     4:::::::::4     ",0
		BYTE "    4::::44::::4     ",0
		BYTE "   4::::4 4::::4     ",0
		BYTE "  4::::4  4::::4     ",0
		BYTE " 4::::4   4::::4     ",0
		BYTE "4::::444444::::444   ",0
		BYTE "4::::::::::::::::4   ",0
		BYTE "4444444444:::::444   ",0
		BYTE "          4::::4     ",0
		BYTE "          4::::4     ",0
		BYTE "          4::::4     ",0
		BYTE "        44::::::44   ",0
		BYTE "        4444444444   ",0

	n5  BYTE "555555555555555555   ",0
		BYTE "5::::::::::::::::5   ",0
		BYTE "5::::::::::::::::5   ",0
		BYTE "5:::::555555555555   ",0
		BYTE "5:::::5              ",0
		BYTE "5:::::5              ",0
		BYTE "5:::::5555555555     ",0
		BYTE "5:::::::::::::::5    ",0
		BYTE "555555555555:::::5   ",0
		BYTE "            5:::::5  ",0
		BYTE "            5:::::5  ",0
		BYTE "5555555     5:::::5  ",0
		BYTE "5::::::55555::::::5  ",0
		BYTE "5::::::::::::::::5   ",0
		BYTE " 5555555555555555    ",0

	n6  BYTE "        66666666     ",0
		BYTE "       6::::::6      ",0
		BYTE "      6::::::6       ",0
		BYTE "     6::::::6        ",0
		BYTE "    6::::::6         ",0
		BYTE "   6::::::6          ",0
		BYTE "  6::::::6           ",0
		BYTE " 6::::::::66666      ",0
		BYTE "6::::::::::::::66    ",0
		BYTE "6::::::66666:::::6   ",0
		BYTE "6:::::6     6:::::6  ",0
		BYTE "6:::::6     6:::::6  ",0
		BYTE "6::::::66666::::::6  ",0
		BYTE " 66:::::::::::::66   ",0
		BYTE "   66666666666666    ",0

	n7  BYTE "7777777777777777777  ",0
		BYTE "7::::::::::::::::::7 ",0
		BYTE "7::::::::::::::::::7 ",0
		BYTE "777777777777:::::::7 ",0
		BYTE "           7::::::7  ",0
		BYTE "          7::::::7   ",0
		BYTE "         7::::::7    ",0
		BYTE "        7::::::7     ",0
		BYTE "       7::::::7      ",0
		BYTE "      7::::::7       ",0
		BYTE "     7::::::7        ",0
		BYTE "    7::::::7         ",0
		BYTE "   7::::::7          ",0
		BYTE "  7::::::7           ",0
		BYTE " 77777777            ",0

	n8  BYTE "     888888888       ",0
		BYTE "   88:::::::::88     ",0
		BYTE " 88:::::::::::::88   ",0
		BYTE "8::::::88888::::::8  ",0
		BYTE "8:::::8     8:::::8  ",0
		BYTE "8:::::8     8:::::8  ",0
		BYTE " 8:::::88888:::::8   ",0
		BYTE "  88:::::::::::88    ",0
		BYTE " 8:::::88888:::::8   ",0
		BYTE "8:::::8     8:::::8  ",0
		BYTE "8:::::8     8:::::8  ",0
		BYTE "8:::::8     8:::::8  ",0
		BYTE "8::::::88888::::::8  ",0
		BYTE " 88:::::::::::::88   ",0
		BYTE "   88888888888888    ",0

	n9  BYTE "     999999999       ",0
		BYTE "   99:::::::::99     ",0
		BYTE " 99:::::::::::::99   ",0
		BYTE "9::::::99999::::::9  ",0
		BYTE "9:::::9     9:::::9  ",0
		BYTE "9:::::9     9:::::9  ",0
		BYTE " 9:::::99999::::::9  ",0
		BYTE "  99::::::::::::::9  ",0
		BYTE "    99999::::::::9   ",0
		BYTE "         9::::::9    ",0
		BYTE "        9::::::9     ",0
		BYTE "       9::::::9      ",0
		BYTE "      9::::::9       ",0
		BYTE "     9::::::9        ",0
		BYTE "    99999999         ",0

	digits DWORD OFFSET n0, OFFSET n1, OFFSET n2, OFFSET n3, OFFSET n4, OFFSET n5, OFFSET n6, OFFSET n7, OFFSET n8, OFFSET n9

.code
main PROC

clock:
	mov DH,0
	mov DL,0
	call Gotoxy

	call fetch_time

	mov EAX,hour
	call split_digits
	call process_time
	call write_time
	call Crlf

	mov EAX,min
	call split_digits
	call process_time
	call write_time
	call Crlf

	mov EAX,sec
	call split_digits
	call process_time
	call write_time

	mov EAX, 1000
	call Delay

	jmp clock
	
exit
main ENDP

fetch_time PROC
	Invoke GetLocalTime, addr time

	movzx EAX, time.whour
	mov hour,EAX

	movzx EAX, time.wminute
	mov min, EAX

	movzx EAX, time.wsecond
	mov sec, EAX

	ret
fetch_time ENDP

split_digits PROC	; will use EAX as input
	mov EDX,0

	mov EBX,10
	idiv EBX
	mov tens,EAX
	mov ones,EDX

	ret
split_digits ENDP
	
process_time PROC
	mov ESI,OFFSET digits
	mov EBX,4
	
	mov EAX,tens
	mul EBX
	mov EAX,[ESI + EAX]
	mov tensAddr,EAX

	mov EAX,ones
	mul EBX
	mov EAX,[ESI + EAX]
	mov onesAddr,EAX

	ret
process_time ENDP

write_time PROC uses ECX EDX ESI EDI
    mov ESI, tensAddr
    mov EDI, onesAddr
    mov ECX, 15

	l1:
		mov EDX, ESI
		call WriteString

		mov EDX, EDI
		call WriteString

		call Crlf

		add ESI, 22
		add EDI, 22
	loop l1

    ret
write_time ENDP


END main