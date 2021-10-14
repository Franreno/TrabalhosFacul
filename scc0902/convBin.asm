; Nome: Francisco Reis Nogueira
; Nusp: 11954374
; Data: 

org 100h

Inicio:
    mov bx, varH
    mov data, bx
    call convertHexToBinary
    call printBinary

Fim:
    nop
    ret


convertHexToBinary proc
        mov bx, data
        ; Store bl part
        mov blHolder, bl
                      
        lea bp, output
                
        Start:
        mov cx, 8
        
        do8bits:
            rcl bh, 1
            mov ah, 30h
            adc ah, 0
            mov [bp], ah
            
            inc bp
            loop do8bits
        
        mov bh, blHolder
        cmp dh, 0
        mov dh, 1
        jz Start
        
        
        ret
endp convertHexToBinary
        
printBinary proc
    lea bp, output
    mov cx, 16
    print:    
        mov dl, [bp]
        mov ah, 2h
        int 21h   
        inc bp
        loop print
       
    ret

endp printBinary
        

varh dw 8271h
vard dw 1200d
data dw 0  
blHolder db 0
output db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0