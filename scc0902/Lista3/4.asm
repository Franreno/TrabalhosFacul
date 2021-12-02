	.data
NRO: .word 100
newline: .asciiz "\n"

enterNumber: .asciiz "Enter loop condition:\n > "

yourNumberIs: .asciiz "Your number is: "



	.text
.globl main

main:
	jal printEnterNumber
	jal scanNumber
	move $t1, $v0
	jal printYourNumberIs
	

	
	printNumber:
		li $v0, 1
		move $a0, $t1
		syscall
	
	jal printNewline
		
	li $t2, 1
	
loop:
	print:
		li $v0, 1
		move $a0, $t2
		syscall
		
		jal printNewline
	
	add $t2, $t2, 1
	ble $t2, $t1, loop
	j exit
	
scanNumber:
	li $v0, 5
	syscall
	jr $ra

printEnterNumber:
	li $v0, 4
	la $a0, enterNumber
	syscall
	jr $ra

printYourNumberIs:
	li $v0, 4
	la $a0, yourNumberIs
	syscall
	jr $ra
	
printNewline:
	li $v0, 4
	la $a0, newline
	syscall
	jr $ra
		
exit:
	li $v0, 0x0A
	syscall
	