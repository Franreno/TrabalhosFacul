	.data
inicio: .word -1
defineInteger: .asciiz "Digite um inteiro:\n > "
newline: .asciiz  "\n"

	.text
li $v0, 4
la $a0, defineInteger
syscall
	
li $v0, 5
syscall

move $t0, $v0
li $t1, 0 # Counter
loop:
	li $v0, 1
	move $a0, $t0
	syscall
	
	li $v0, 4
	la $a0, newline
	syscall
	
	sub $t0, $t0, 1
	bge $t0, $t1, loop
	
exit:
	li $v0, 0x0A
	syscall
