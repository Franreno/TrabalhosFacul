	.data
asterisco: .asciiz "*"
newline: .asciiz "\n"
defineInteger: .asciiz "Digite um inteiro:\n > "

maxLines: .word -1

	.text
.globl main

main:
	li $v0, 4
	la $a0, defineInteger
	syscall
	
	#Read integer
	li $v0, 5
	syscall
	
	move $t0, $v0
	
#Set columns to 0
lineLoop:
	li $t2, 0
	columnLoop:
		li $v0, 4
		la $a0, asterisco
		syscall
				
		add $t2, $t2, 1
		blt $t2, $t0, columnLoop
		
	la $a0, newline
	syscall
	
	#Amount of columns to print
	sub $t0, $t0, 1
	bgt $t0, $zero, lineLoop
