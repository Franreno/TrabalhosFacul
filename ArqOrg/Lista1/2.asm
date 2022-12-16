
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

VALMAX db 32h

Inicio:   
    mov ax, 0
    mov al, VALMAX
    mov bx, 0
    
Loop:
    cmp al,bl
    jz Fim
    inc bl
    jmp Loop

Fim:
    nop
    ret