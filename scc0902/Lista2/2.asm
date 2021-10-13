;Search for a number in an array


org 100h

Inicio:    
    lea bp, VETOR
    mov bx, TAM
    mov ax,0 
    mov al, VALOR
Meio:       
    cmp [bp], al
    jz encontrou
    inc bp
    dec bx
    cmp bx,0
    jz Fim
    jmp Meio
    encontrou:
        mov ah,1
Fim:
    cmp ah, 1
    jz achou
    jmp nAchou
    achou:         
        mov ax, seg ACHOUM
        mov ds, ax
        mov dx, offset ACHOUM
        mov ah, 9h
        int 21h
        jmp Stop
            
    nAchou:  
        mov ax, seg NACHOUM
        mov ds, ax
        mov dx, offset NACHOUM
        mov ah, 9h
        int 21h
        jmp Stop
Stop:   
    nop
    ret
      

VETOR db 1,4,2,1,4,12,43,24,65,2,34,12,67,95,32,12,75,23,6,3,4,5,2
TAM dw 23
VALOR db 65  
ACHOUM db "ACHOU$"
NACHOUM db "NAO ACHOU$"