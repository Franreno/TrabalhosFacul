; Nome: Francisco Reis Nogueira
; Nusp: 11954374
; Dia: 

org 100h

Inicio:
    ;Screen setup
    mov ah,0
    mov al,03h
    int 10h
    
    
getCursorValues:
    mov ax, 3h
    int 33h
    mov xPos,cx
    mov yPos,dx
    mov botoes, bx
    ;Write at the screen
    call printXYValues
    call listenToEsc
    jmp getCursorValues

Fim:
   nop
   hlt
   

printXYValues proc
    ;mov cx,1
    ;mov bh, 0
    ;mov bl, 7
    
    mov ax, xPos
    mov Data, ax
    call printHexa
    call printSpace
    
    mov ax, yPos
    mov Data, ax
    call printHexa
    call printSpace
    call newline
    
    ret
endp printXYValues

printHexa proc
    mov ax, Data
    and ax, 00F0h
    shr ax,4   
    mov holder, al
    call printChar
    
    mov ax, Data
    and ax, 000Fh
    mov holder, al
    call printChar
 
     ret 
endp printHexa

printChar proc
    cmp al, 0Ah
    jb Number
    jmp Alpha
    
    
    Alpha:
        sub al, 0Ah
        add al, 'A'
        jmp printDigit
    
    Number:
        add al, '0'
        jmp printDigit
        
    printDigit:
        mov ah, 0Eh
        int 10h
        ret
     
endp printChar

newline proc
    mov ah, 0Eh
    mov al, 0Dh
    int 10h
    
    ret
endp newline

printSpace proc
    mov ah, 0Eh
    mov al, ' '
    int 10h
    
    ret
endp printSpace

 
listenToEsc proc
    cmp bl, 0
    jnz Fim
                
    ret
endp listenToEsc

xPos dw 0
yPos dw 0     
Data dw 0
holder db 0
botoes dw 0