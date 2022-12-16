
; You may customize this and other start-up templates; 
; The location of this template is c:\emu8086\inc\0_com_template.txt

org 100h

; add your code here

Inicio:
    lea bp, va          ;Gets address of bp
    mov dx, Size        ;Gets size value
    
    mov bx,0            ;Acumulator
    mov bl,0            ;Using bl because va is db
    
Loop:
    add bl, [bp]        ; Adds value of array from *bp
    inc bp              ; Increments bp. bp + 1
    dec dx              ; Dec size. 
    jnz loop            ; Keeps on loop until dx is 0
    
    mov varEnd, bx      ; Mov the value of bx to the final value

Fim:
    nop
    ret

VA db 1,2,3,4,5,6,7,8,9,10
Size dw 10     
varEnd dw ?
