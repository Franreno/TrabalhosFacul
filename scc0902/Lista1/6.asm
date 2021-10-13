org 100h

Inicio:
    lea bp, DADO1   ; Pointer for Dado1
    lea si, DADO2   ; Pointer for Dado2                   
    lea di, SOMA    ; Pointer for Soma
          
    mov dx, SIZE    ; Size of arrays  
    
    ;Start at the end of arrays
    dec SIZE
    add bp, SIZE    ; Go to DADO1[len(DADO1)-1]
    add si, SIZE
    add di, SIZE
    inc SIZE
    
    mov ax,0  ; ah -> accumulator. al->sum
    mov bx,0  ; bh-> Flag for CF. bl->sum
       
Meio:
    mov al, [bp]     ; Get value from DADO1
    mov bl, [si]     ; Get value from DADO2
  
    add ah, al       ; Add both values
    add ah, bl
  
    ;Check if previous sum has exceeded 10
    cmp bh, 1
    jz bhIsSet
    jmp startCmp
            
    ; If its set then add +1 to the sum
    bhIsSet:
        add ah,1
        mov bh,0
   
    ; Start comparasion if the value has exceeded 10
    startCmp: 
    cmp ah, 10      ; Comp if al+bl > 10
         
    jc menorQDez    ; al+bl < 10 (CF = 1)
    jmp maiorIgualQDez   ; al+bl > 10 (CF = 0 && ZF = 0)
    
         
    menorQDez:
        mov [di], ah     ; Adds the value to SOMA
        jmp endCmp
    maiorIgualQDez:
        sub ah, 10       ; subtract 10 from ah
        mov bh, 1        ; set the +1 flag
        mov [di], ah     ; Adds the value to SOMA
        jmp endCmp
    
    endCmp:
        dec bp           ; Go to the next value in DADO1
        dec si           ; Go to the next value in DADO2
        dec di           ; Go to the next vaalue in SOMA
        
        ;Clear counters and accumlators
        mov al,0
        mov bl,0
        mov ah,0
        
        ; Decrement size and check if it has reached the end
        dec dx
        cmp dx, 0
        jz Fim
        jmp Meio
      
Fim:
    ; Print values from SOMA
    lea bp, SOMA    ;Pointer to SOMA
    mov bx, SIZE    ;Counter to size
    mov dx, 0 
    
    printLoop:
        mov dl, [bp] ; dl is the print register
        add dl, 48   ; 48 is '0' char
        mov ah, 2h   ; Instruction to print on the screen
        int 21h      ; Do the instruction above
        inc bp       ; Increment the pointer
        dec bx       ; Decrement the counter
        cmp bx,0     ; Check if it ended
        jz Stop
        jmp printLoop
           
 
Stop:   
    nop
    ret

DADO1 db 1,4,2,1,6,2,4,7,7,8,4,2,3,4,1,2,3,4,5,7,8,4,2,1,3,2,5,2,1,8
DADO2 db 2,2,1,6,3,1,7,3,1,5,1,5,8,2,5,1,4,6,2,5,8,1,2,5,1,4,6,7,1,8
SOMA  db 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
;For this specific arrays result should be 363794209358166380836546471936
SIZE dw 30
