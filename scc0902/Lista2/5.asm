org 100h

; add your code here

Inicio:
    lea bp, MSG
    
    mov bx,0
    
Meio:    
    ;Verificar se eh maiusculo
    cmp [bp], 90
    JBE ehMaiusculo ; JBE: <=
    jmp naoEhMaiusculo
    
    ehMaiusculo:
        ;veririfcar se eh 90 'Z'
        cmp [bp], 90
        jz ehLetraBigZ          
        
        add [bp], 1
        jmp endUpperLowerCase
        
        ehLetraBigZ:
            mov [bp], 65
            jmp endUpperLowerCase
 
    naoEhMaiusculo:
        ;verificar se eh 'z'
        cmp [bp], 122
        jz ehLetraz
        add [bp], 1
        jmp endUpperLowerCase
        
        ehLetraz:
            mov [bp], 97
            jmp endUpperLowerCase
            
        
    endUpperLowerCase:
    inc bp
    cmp [bp], 0
    jz printf
    jmp Meio
  

printf:    
    lea bp, MSG
    printLoop:
        cmp [bp], 0
        jz Fim
        mov dl, [bp]
        mov ah, 2h
        int 21h
        inc bp
        jmp printLoop
  
   
Fim:
    nop
    ret



MSG db "Hello World", 0
Size db ?