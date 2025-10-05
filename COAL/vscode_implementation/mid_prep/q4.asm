INCLUDE Irvine32.inc


.data

byteVal SBYTE -1
wordVal word 1000h


.code
    main PROC

    mov eax, 0
    movzx eax, byteVal  ; moves the val while treating it as unsigned

    movsx ebx, byteVal  ; moves it, while keeping it signed


    mov ecx, 0
    xchg cx, wordVal

    call dumpRegs

    



    exit

main ENDP

END main