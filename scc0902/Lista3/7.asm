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
li $t1, 0
lineLoop:
	#Amount of columns to print
	add $t1, $t1, 1
	
	li $t2, 0
	columnLoop:
		li $v0, 4
		la $a0, asterisco
		syscall
				
		add $t2, $t2, 1
		blt $t2, $t1, columnLoop
		
	la $a0, newline
	syscall
	
	blt $t1, $t0, lineLoop