
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; add your code here
Inicio:
    ;Clear registers
    mov ax,0
    mov bx,0
    mov ah,VAL1
    mov al,VAL2

Meio:
    add bl, ah
    dec al
    cmp al,0
    jz Fim
    jmp Meio

Fim:        
    mov RESMULT, bx
    nop
    ret


VAL1 db 4
VAL2 db 3
RESMULT dw ?
