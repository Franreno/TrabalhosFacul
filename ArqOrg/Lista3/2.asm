	.data
dado1: .word 01234567
dado2: .word 76543210
soma:  .word 00000000

	.text
.globl main

main:
	li $t0, 0
	lw $t1, dado1
	add $t0, $t1, $t0
	lw $t1, dado2
	add $t0, $t1, $t0
	sw $t0, soma
	
	li $v0, 1
	lw $a0, soma
	syscall
	
	li $v0, 0x0A
	syscall