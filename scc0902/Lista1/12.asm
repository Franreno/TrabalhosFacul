
;Copiar uma String (TEXTO1), terminada por ‘\0’, para uma outra string (TEXTO2),
;também deve terminar com o ‘\0’. O programa deve mover os dados de uma 
;string para outra string, inicialmente vazia.


org 100h

Inicio:
    lea bp, TEXTO1  ; Pointer to TEXTO1
    mov bx,0        ; Size of array
    
    strlen:
        cmp [bp], '\'
        jz isNextZero
        jmp nextWasNotZero
        
        isNextZero:
            inc bp
            cmp [bp], '0'
            inc bl
            inc bp
            jmp endStrlen
             
        nextWasNotZero:
            inc bl
            inc bp
            jmp strlen
 
        endStrlen:
            mov Size, bl
    
    ;With the length we can clear the amount of bytes of TEXTO2
           
    lea bp, TEXTO2
    mov ax, 0
    mov al, Size
    clearBytes:
            mov [bp], 0
            inc bp
            dec al
            cmp al, 0
            jz Meio
            jmp clearBytes
            
     
Meio:
    ; Copy one string to another      
    mov Size,bl
    lea bp, TEXTO1
    lea si, TeXTO2
    mov ax,0
    mov al,Size
    strcpy:
        mov ah, [bp]
        mov [si], ah
        inc bp
        inc si
        dec al
        cmp al,1 ;Last one has to be placed with \0
        jz fillWithZero
        jmp strcpy
        fillWithZero:
            mov [si], '\'
            inc si
            mov [si], '0'

Fim:    
    lea bp, TEXTO2
    printString:
        mov dl, [bp]
        mov ah, 2h
        int 21h
        inc bp
        dec bl
        cmp bl,1
        jz Stop
        jmp printString
        
Stop:
    nop
    ret


TEXTO1 db 'H','e','l','l','o',' ','W','o','r','l','d','\0'
TEXTO2 db 0
Size db 0