org 100h

Inicio:    
    lea bp, String
    
    ;Screen setup
    mov ah, 0
    mov al, 03h
    int 10h
    
    ;Read until its an 0Dh
    ;Read from the screen
    mov dx,0
    mov bl,7
    mov cx,1
    ReadChars:
        ;Read keyboard
        mov ah,0
        int 16h
        mov [bp], al  
        
        ;Write what was written to the screen     
        mov ah, 09h
        int 10h
        
        ;Increase cursor column
        inc dl
        mov ah,2
        int 10h
        
        ;Check for enter, aka 0Dh
        inc bp
        cmp al, 0Dh
        jz Meio
        jmp ReadChars
    
    
Meio:
    ;Encript String 
    lea bp, String
    encript:   
        inc [bp]
        inc bp
        cmp [bp], 0Dh
        jnz  encript
        
        
    lea si, String
    
    mov bh, 0 ;Page 0
    mov bl, 7 ;Color 7 (light gray)
    mov cx, 1 ;Print one character
    
    ;Set cursor position
    mov dh, 2 ;Cursor row = 2
    mov dl, 0 ;Cursor column = 0
    mov ah,2
    int 10h    
    
    printf:
        ;Read from the string and print on the screen
        mov al, [si]
        mov ah, 09h
        int 10h  
        
        ;Move cursor to the right
        inc dl
        mov ah,2
        int 10h
             
        ;Check for ending
        inc si
        cmp [si], 0Dh
        jz Fim
        jmp printf
    

Fim:
    nop
    ret
    
 
String db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0