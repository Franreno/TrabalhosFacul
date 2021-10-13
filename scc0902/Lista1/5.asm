
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; add your code here

Inicio:      
    lea bp, VETINI      ; Gets addres of array
    mov dx, TOTVAL      ; Times to sum
    
    mov bx,0
    mov bl,0

Meio:
    add bl, [bp]
    inc bp
    dec dx
    jnz Meio
    
    mov result, bx
    
Fim:
    nop
    ret




VETINI db 1,2,3,4,5,6,7,8,9,10
TOTVAL dw 5
RESULT dw ?