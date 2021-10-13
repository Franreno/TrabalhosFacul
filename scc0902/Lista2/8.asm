org 100h

; add your code here

Inicio:
    lea bp, String
        
    
    readChars:
        mov ah, 1
        int 21h
        mov [bp], al
        inc bp
        cmp al, 0Dh
        jz Meio
        jmp readChars
       
Meio:  
    lea bp, String
    encript:
        mov al, [bp]
        inc [bp]
        inc bp
        cmp [bp], 0Dh
        jnz encript
     
        
    lea bp, String
    printf:
         mov dl, [bp]
         mov ah,2
         int 21h
         inc bp
         cmp [bp], 0Dh
         jz Fim
         jmp printf


Fim:
    nop
    ret
                 
                 
                 
 String db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0