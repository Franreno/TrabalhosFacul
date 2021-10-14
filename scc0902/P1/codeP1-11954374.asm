; Nome: Francisco Reis Nogueira
; Nusp: 11954374
; Data: 14/10/2021

org 100h

Inicio:
    lea bp, MSG         ; Ponteiro para MSG 
    lea si, CHAVE       ; Ponteiro para CHAVE
    lea di, CRIPTO      ; Ponteiro para CRIPTO
      
    mov cl, CHAVESIZE   ; Contador do tamanho da chave

Meio:
    ; Rodar a string ate chegar no 00h
    
    mov al, [si]        ; Pega o valor da chave
    add [bp], al        ; Adiciona no valor da mensagem
    
    mov al, [bp]        ; Pega o valor da mensagem
    mov [di], al        ; Coloca na mensagem criptografada
    
    ; Incrementa ponteiros e decrementa o contador da chave
    inc bp              
    inc si
    inc di
    dec cl
    
    ; Confere se o contador da chave ja chegou no final
    cmp cl, 0
    jz restartChave
    
    ; Confere se a mensagem acabou, chegou em um 00h
    acabouMSG:
        cmp [bp], 00h
        jz printMSG
        jmp Meio
    
    ; Reinicia a chave, aponta pro comeco dela
    ; e restatura o valor do contador
    restartChave:
        mov cl, CHAVESIZE
        lea si, CHAVE
        jmp acabouMSG
        
    
printMSG:
    ; Coloca um valor de 00h no final da mensagem criptografada
    mov [di], 00h
    
    
    lea di, CRIPTO      ; Aponta pro comeco de cripto
    
    ; Imprime caractere por caractere ate chegar no 00h
    doPrint:
        mov dl, [di]    
        mov ah, 02h     ; Instrucao de impressao na tela
        int 21h
        inc di
        cmp [di], 00h
        jz Fim
        jmp doPrint
        
    
Fim:
    ; Espera um input do usuario para terminar o programa        
    getInput:
        mov ah, 01h     ; Instrucao de input do usuario
        int 21h
        
    nop
    ret


; Chave sempre tem tamanho 5
CHAVESIZE db 5            

;Tamanho minimo de 10
CRIPTO db 0,0,0,0,0,0,0,0,0,0
 
 
;CASOS DE TESTE. Descomentar a que for usar


MSG db 'A','E','I','O','U','A','B','C','D','E', 00h
CHAVE db 1,2,3,4,5
;;Codificada: B G L S Z B D F H J
  
 
;MSG db 'H','E','L','L','O','W','O','R','L','D', 00h
;CHAVE db 1,2,3,4,5      
;;Codificada: I G O P T X Q U P I


;MSG db 'H','E','L','L','O','W','O','R','L','D', 00h
;CHAVE db 2,2,2,2,2      
;;Codificada: J G N N Q Y Q T N F
                                                    
                                                    
;MSG db 'H','E','L','L','O','W','O','R','L','D', 00h
;CHAVE db 1,2,3,4,5      
;;Codificada: I G O P T X Q U P I
                                                    
                                                    
;MSG db 'B','o','a','.','p','r','o','v','a','.','p','a','r','a','.','t','o','d','o','s','!',00h 
;CHAVE db 0,0,0,0,0      
;;Codificada: B o a . p r o v a . p a r a . t o d o s !
                                                    
                                                    
;MSG db 'B','o','a','.','p','r','o','v','a','.','p','a','r','a','.','t','o','d','o','s','!',00h 
;CHAVE db 1,2,3,1,2      
;;Codificada: C q d / r s q y b 0 q c u b 0 u q g p u "


;MSG db 'F','r','a','n','c','i','s','c','o','.','R','e','i','s','.','N','o','g','u','e','i','r','a',00h
;CHAVE db 1,1,9,5,4
;;Codificada G s j s g j t l t 2 S f r x 2 0 p p z i j s j