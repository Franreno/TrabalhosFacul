	.data
inicio: .word 0
final:  .word 0
incr:	.word 0

enterInicio: .asciiz "Digite o inicio:\n > "
enterFinal:  .asciiz "Digite o final:\n > "
enterIncr:   .asciiz "Digite o valor de incremento:\n > "
newline: .asciiz "\n"

	.text

.globl main

main:
	jal printEnterInicio
	jal scanNumber
	sw $v0, inicio
	
	jal printEnterFinal
	jal scanNumber
	sw $v0, final
	
	jal printEnterIncr
	jal scanNumber
	sw $v0, incr
	
	lw $t1, inicio
	
	lw $t2, incr
	
	lw $t3, final
	
	loop:
		jal printNumberInicio
		jal printNewline
		add $t1, $t1, $t2
		sw $t1, inicio
		
		ble $t1, $t3, loop	
	
	
	j exit

scanNumber:
	li $v0, 5
	syscall
	jr $ra

printNumberInicio:
	li $v0, 1
	lw $a0, inicio
	syscall
	jr $ra

printNewline:
	li $v0, 4
	la $a0, newline
	syscall
	jr $ra

printEnterInicio:
	li $v0, 4
	la $a0, enterInicio
	syscall
	jr $ra


printEnterFinal:
	li $v0, 4
	la $a0, enterFinal
	syscall
	jr $ra

printEnterIncr:
	li $v0, 4
	la $a0, enterIncr
	syscall
	jr $ra


exit:
	li $v0, 0x0A
	syscall