
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

nro equ 100

Inicio:
    mov ax, nro
    mov bx, 0
    
Loop:
    cmp ax,bx
    jz Fim
    inc bx
    jmp Loop
Fim:
    nop
    ret    





