INCLUDE Irvine32.inc

.data
    ; Buffers
    inputBuffer     BYTE    256 DUP(0)
    reversedBuffer  BYTE    256 DUP(0)
    
    ; Stack for word offsets
    wordOffsets     DWORD   64 DUP(?)   ; Can hold up to 64 words
    wordCount       DWORD   0
    
    ; Strings
    msgEnter        BYTE    "Enter sentence: ", 0
    msgCount        BYTE    "Word Count: ", 0
    msgPush         BYTE    "Stack Push Order:", 0Dh, 0Ah, 0
    msgPop          BYTE    "Stack Pop Order:", 0Dh, 0Ah, 0
    msgReverse      BYTE    "Reversed sentence: ", 0
    space           BYTE    ' '

.code
main PROC
    ; --- 1. Ask user to enter sentence ---
    MOV EDX, OFFSET msgEnter
    CALL WriteString
    
    MOV EDX, OFFSET inputBuffer
    MOV ECX, SIZEOF inputBuffer - 1
    CALL ReadString             ; EAX = length of string read
    
    ; --- 2. Split into words ---
    ; This loop parses the inputBuffer. It finds the start of each
    ; word and saves its offset in the wordOffsets array.
    ; It also replaces spaces with NULLs in the inputBuffer.
    
    MOV ESI, OFFSET inputBuffer     ; ESI = source (input)
    MOV EDI, OFFSET wordOffsets     ; EDI = destination (offsets array)
    MOV ECX, 0                      ; ECX = word counter
    
ParseLoop:
    ; Skip leading spaces
    SkipSpaces:
        MOV AL, [ESI]
        CMP AL, ' '
        JE IsSpace
        CMP AL, 0
        JE ParseDone           ; End of string, we're done
        JMP FoundWordStart     ; Not a space or null, must be a word
    IsSpace:
        INC ESI
        JMP SkipSpaces

    FoundWordStart:
        MOV [EDI], ESI         ; Save the offset of the word
        ADD EDI, TYPE DWORD    ; Move to next slot in offsets array
        INC ECX                ; Increment word counter

    ; Find the end of the word (a space or NULL)
    FindWordEnd:
        INC ESI
        MOV AL, [ESI]
        CMP AL, ' '
        JE FoundWordEndSpace
        CMP AL, 0
        JE ParseDone           ; End of string, we're done
        JMP FindWordEnd        ; Still in the word
        
    FoundWordEndSpace:
        MOV BYTE PTR [ESI], 0  ; Put a NULL terminator where the space was
        INC ESI
        JMP ParseLoop

ParseDone:
    MOV wordCount, ECX         ; Save the final word count

    ; --- Display Word Count ---
    MOV EDX, OFFSET msgCount
    CALL WriteString
    MOV EAX, wordCount
    CALL WriteDec
    CALL Crlf

    ; --- Display Stack Push Order (Requirement) ---
    MOV EDX, OFFSET msgPush
    CALL WriteString
    MOV ECX, wordCount
    MOV ESI, OFFSET wordOffsets
PushTraceLoop:
    MOV EDX, [ESI]             ; EDX = offset of the word
    CALL WriteString           ; Print the word
    CALL Crlf
    ADD ESI, TYPE DWORD
    LOOP PushTraceLoop

    ; --- 2b. PUSH each word offset onto the stack ---
    MOV ECX, wordCount
    MOV ESI, OFFSET wordOffsets
PushToStackLoop:
    PUSH [ESI]                 ; PUSH the offset
    ADD ESI, TYPE DWORD
    LOOP PushToStackLoop

    ; --- Display Stack Pop Order (Requirement) ---
    MOV EDX, OFFSET msgPop
    CALL WriteString
    MOV ECX, wordCount
    MOV ESI, OFFSET wordOffsets
    ; Go to the end of the array to print in reverse
    MOV EAX, ECX
    IMUL EAX, TYPE DWORD
    ADD ESI, EAX               ; ESI now points just AFTER the last offset
PopTraceLoop:
    SUB ESI, TYPE DWORD        ; Move back to the last valid offset
    MOV EDX, [ESI]             ; EDX = offset of the word
    CALL WriteString           ; Print the word
    CALL Crlf
    LOOP PopTraceLoop

    ; --- 3. POP into new array ---
    MOV EDI, OFFSET reversedBuffer  ; EDI = destination (reversed)
    MOV ECX, wordCount
PopLoop:
    POP ESI                    ; ESI now has the word offset (in reverse)
    
    ; Copy the word from [ESI] to [EDI]
    CopyLoop:
        MOV AL, [ESI]          ; Get a character
        CMP AL, 0              ; Is it the NULL terminator?
        JE WordCopied
        MOV [EDI], AL          ; Store the character
        INC ESI
        INC EDI
        JMP CopyLoop
        
    WordCopied:
        MOV AL, space          ; Add a space after the word
        MOV [EDI], AL
        INC EDI
        LOOP PopLoop

    ; Done. Null-terminate the new string (overwriting the last space)
    DEC EDI
    MOV BYTE PTR [EDI], 0

    ; --- 4. Display reversed sentence ---
    MOV EDX, OFFSET msgReverse
    CALL WriteString
    
    MOV EDX, OFFSET reversedBuffer
    CALL WriteString
    CALL Crlf

    INVOKE ExitProcess, 0
main ENDP
END main