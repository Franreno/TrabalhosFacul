
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

;Dividir um valor (A) de 16 bits por 2, com divisão inteira, 
;salvando o resultado em memória (DIV2).

org 100h

     
Inicio:
    mov ax, 8
    mov bl, 2
    div bl    
    
Fim:
    nop
    ret


A dw 8

