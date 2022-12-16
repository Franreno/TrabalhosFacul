
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

;Contagem regressiva ate 0

valmax dw 50  
  
Inicio:
    mov ax, valmax
    mov bx, 0

Loop:        
    cmp ax,bx
    jz Fim
    dec ax
    jmp Loop

Fim:
    nop
    ret




