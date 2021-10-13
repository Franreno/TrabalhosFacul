; Nome: Francisco Reis Nogueira
; Nusp: 11954374
; Dia: 

org 100h

Inicio:
    
    randGen:
        MOV AH, 00h  ; interrupts to get system time        
        INT 1AH      ; CX:DX now hold number of clock ticks since midnight      

        mov  ax, dx
        xor  dx, dx
        mov  cx, 10    
        div  cx       ; here dx contains the remainder of the division - from 0 to 9



Meio:
    mov RandomNumber, dl
    
    ;ReadChar
    ReadChar:
        mov ah,1
        int 21h
        sub al, '0'
        
        cmp al, 9
        ja invalido
        jmp endReadChar
        invalido:
            mov ax, seg msgValorInvalido
            mov ds, ax
            mov dx, offset msgValorInvalido
            mov ah, 9h
            int 21h
            call newline
            jmp readChar        
        
        endReadChar:
        cmp RandomNumber, al
        je ok
        ja maior
        jb menor
        
        ok:
            mov ax, seg msgOK
            mov ds, ax
            mov dx, offset msgOK
            mov ah, 9h
            int 21h
            call newline
            jmp Fim
            
        maior:
            mov ax, seg msgMaior
            mov ds, ax
            mov dx, offset msgMaior
            mov ah, 9h
            int 21h
            call newline
            jmp ReadChar
            
        menor:
            mov ax, seg msgMenor
            mov ds, ax
            mov dx, offset msgMenor
            mov ah, 9h
            int 21h
            call newline
            jmp ReadChar
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


msgMaior db "Maior$"
msgMenor db "Menor$"
msgOK db "Ok$"      
msgValorInvalido db "Valor invalido$"
RandomNumber db 0
