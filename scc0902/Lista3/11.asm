	.data
buffer: .space 64
enterString: .asciiz "Digite uma string:\n > "

	.text
	
.globl main

main:
	li $v0, 4
	la $a0, enterString
	syscall
	
	#Read string
	li $v0, 8
	la $a0, buffer
	li $a1, 64
	syscall
	
	#Print string
	li $v0, 4
	la $a0, buffer
	syscall
	
	
	li $v0, 0x0A
	syscall