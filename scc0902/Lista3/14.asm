	.data
NRO: .word -1
defineInteger: .asciiz "Digite um inteiro:\n > "

	.text
.globl main

main:
	li $v0, 4
	la $a0, defineInteger
	syscall
	
	li $v0, 5
	syscall
	
	sw $v0, NRO
	
	lw $t0, NRO
	li $t1, 0 #Counter
	li $s1, 1 #Result
	
	loop:
		mul $s1, $s1, $t0
		
		sub $t0, $t0, 1
		bgt $t0, $t1, loop
	
	li $v0, 1
	move $a0, $s1
	syscall
	
	li $v0, 0x0A
	syscall