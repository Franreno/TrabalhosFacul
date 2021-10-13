
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

;Multiplicar um valor (A) de 16 bits por 4, usando deslocamento de bits e salvar o resultado em
;memória (X4). O valor de 16 bits possui no máximo 10 bits sendo usados para codificar o valor inicial
;de A.

    
Inicio:
    mov ax, a
    shl ax, 2   ; x \cdot 2^n. x->destination and n->count (2)
            

Fim:
    nop
    ret


A dw 10
