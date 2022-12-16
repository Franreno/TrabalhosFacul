.data

dado1: .word 01234567
dado2: .word 76543210
soma:  .word 00000000

.text

.globl main

main:
	lw $t0, dado1
	lw $t1, dado2
	li $t2, 0
	add $t2, $t0, $t1
	sw $t2, soma
	
	li $v0, 1
	lw $a0, soma
	syscall
	
	li $v0, 0x0A
	syscall