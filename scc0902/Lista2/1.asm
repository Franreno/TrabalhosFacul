;Determinar se um n�mero � par ou �mpar. O valor deve estar armazenado na vari�vel VALOR,
;onde o programa deve exibir na tela a mensagem �PAR� se o n�mero for par
;ou �IMPAR� se o n�mero for �mpar.

org 100h

Inicio:
    mov ax,0
    mov al,VALOR
    mov bx,0
    mov bl,2

Meio:
    div bl
    cmp ah, 0
    jz isEven
    jmp isOdd
    isEven:    
        mov bx, seg isEvenM
        mov ds, bx
        mov dx, offset isEvenM
        mov ah, 9h
        int 21h
        jmp Fim
    isOdd:     
        mov bx, seg isOddM
        mov ds, bx
        mov dx, offset isOddM
        mov ah, 9h
        int 21h
        jmp Fim

Fim:   
    nop
    ret





VALOR db 8
isEvenM db "PAR$"
isOddM db "Impar$"