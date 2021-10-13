
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

Inicio:
    mov ax, var1
    mov bx, var2
    mul bx ; ax \cdot bx
    
    ;Stored into DX:AX
     
Fim:
    nop
    ret


var1 dw 2000h
var2 dw 100h
