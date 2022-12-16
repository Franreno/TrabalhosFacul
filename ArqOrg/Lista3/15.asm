# Sort an array

	.data
list: .word 44,66,76,27,61,94,11,74,93,91,89,19,82,77,39,20,80,95,24,87,54,42,73,85,14,15,38,86,88,69,50,81,7,62,49,3,78,64,28,59,55,21,99,51,43,31,9,17,23,90,10,40,47,18,63,83,34,35,84,30,4,92,75,5,37,53,79,41,16,45,60,46,2,70,22,71, 33, 26, 67, 1, 65, 58, 13, 56, 48, 25, 98, 8, 100, 6, 72, 97, 32, 29, 12, 36, 52, 57, 96, 68
listSize: .word 100

space: .asciiz " "

	.text
	
.globl main

main:
	li $s0, 0 # main Counter
	lw $s7, listSize
	
	mainLoop:
		move $t0, $s0 # i
		move $t1, $s0 
		add $t1, $t1, 1 # i + 1
		
		sll $t0, $t0, 2 # Multiply by four
		sll $t1, $t1, 2 # Multiply by four
		
		lw $s1, list($t0)
		lw $s2, list($t1)
		
		# Check
		bgt $s1, $s2, swap
		add $s0, $s0, 1
		
		j jumpSwap
		
		swap:
			# $s1 > $s2
			sw $s1, list($t1)
			sw $s2, list($t0)
			
			#restart counters
			li $s0, 0
			j jumpSwap
			
			
		jumpSwap:			
			blt $s0, $s7 mainLoop
	
	li $s0, 0
	printArray:
		move $t0, $s0
		sll $t0, $t0, 2
		
		lw $a0, list($t0)
		li $v0, 1
		syscall
		
		li $v0, 4
		la $a0, space
		syscall
	
		add $s0, $s0, 1
		blt $s0, $s7 printArray


	j exit
	
exit:
	li $v0, 0x0A
	syscall
