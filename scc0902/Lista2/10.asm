; Nome: Francisco Reis Nogueira
; Nusp: 11954374
; Dia: 

org 100h

Inicio:
    lea bp, msg
    mov bx, bp
    
    ;print normal hello world
    mov ax, seg msg
    mov ds, ax
    mov dx, offset msg
    mov ah, 9h
    int 21h
    call newline


    goToEnd:
        mov al, [bp]
        cmp [bp], 24h
        jz printInvertido
        inc bp
        jmp goToEnd
        
    printInvertido:
        dec bp
        mov dl, [bp]
        mov ah, 2h
        int 21h
        cmp bp, bx
        jz endPrintInvertido
        jmp printInvertido
 
    endPrintInvertido:
        call newline
    printUpper:
        cmp [bp], 'Z'
        ja lowerChar
        jmp endLowerUpper
        
        lowerChar:
            sub [bp], 32
            jmp endLowerUpper
        
        endLowerUpper:
            mov dl, [bp]
            mov ah, 2h
            int 21h
            inc bp
            cmp [bp], 24h ; '$'
            jz Fim
            jmp printUpper        

Fim:
   nop
   ret

newline proc
    mov dl, 10
    mov ah, 02h
    int 21h
    mov dl, 13
    mov ah, 02h
    int 21h
    
    ret
endp newline


msg db "Hello World$"