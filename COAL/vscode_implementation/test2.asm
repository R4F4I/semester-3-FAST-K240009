INCLUDE Irvine32.inc

.data
  val1 WORD 50

.code

main PROC
  mov   eax, -100         ; Load first value
  cwd
  idiv  val1              ; EAX * val1
  ; Result: EDX = 0xFFFFFFFF, EAX = 0xFFE17B80
  ; This is the 64-bit representation of -2,000,000.

call writeint
  
call dumpregs


exit
main ENDP

END main