; The Task: You have a 3x3 matrix of Bytes.
;     Define a predefined 2D array in data.
;     Iterate through the matrix using Row-Major calculation.
;     Calculate the Sum of each row.
;     If the sum is greater than 15, write the string "PASS" into a status array using String Primitives (MOVSB). 
;     If less/equal, write "FAIL".
;     Assume the status array is a simple 1D buffer that stores these results sequentially.


INCLUDE Irvine32.inc


.data
    ; 3 Rows, 3 Columns (Bytes)
    matrix  BYTE  1, 2, 3
            BYTE  5, 6, 7
            BYTE  2, 1, 2
    
    ROW_SIZE = 3
    NUM_ROWS = 3
    
    passStr BYTE "PASS ",0
    failStr BYTE "FAIL ",0
    
    report  BYTE 50 DUP(?)   ; Output string buffer

.code
main PROC
mov edi, offset report  ;report=[edi] is dest where we will copy the string from [esi], then copy it from [edi] to edx, then call writestring
mov ebx, 0

RowLoop:
    cmp ebx, NUM_ROWS
    jge done

    mov esi, 0
    mov eax, 0

    colLoop:
        cmp esi, ROW_SIZE
        jge CheckSum

        ; addr = base + rowI*rowSize + colI
        mov ecx, ebx
        imul ecx, ROW_SIZE
        add ecx, esi

        movzx edx, matrix[ecx]
        add eax, edx 

        inc esi
        jmp colLoop
    checkSum:
        cmp eax, 15
        ja writePass
    writeFail:
        mov esi, offset failStr     ; set esi to addr to failStr, 
        mov ecx, lengthOf failStr-1
        jmp copyString
    writePass:
        mov esi, offset passStr
        mov ecx, lengthOf passStr-1
        
    copyString:
        cld
        rep movsb   ; copy from [esi] to [edi]

    inc ebx
    jmp RowLoop

done:
mov edx, offset report ; val copied in report from esi
; failStr -> offset = [esi] -> movSb -> [edi]=[esi], but [edi] = report, -> report
call writeString
call crlf


exit
main ENDP
end main