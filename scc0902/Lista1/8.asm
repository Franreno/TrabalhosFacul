
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; add your code here
    
Inicio:
    mov al, var1
    mov bl, var2
    
    mul bl
    
Fim:
    nop
    ret


var1 db 2
var2 db 4