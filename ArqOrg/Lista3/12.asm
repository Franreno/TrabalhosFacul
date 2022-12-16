	.data
str1: .space 64
str2: .space 64
str3: .space 128

enterString: .asciiz "Digite uma string:\n > "

	.text
	
.globl main

main:
	li $v0, 4
	la $a0, enterString
	syscall
	
	#Read string
	li $v0, 8
	la $a0, str1
	li $a1, 64
	syscall
	
	li $v0, 4
	la $a0, enterString
	syscall
	
	#Read string
	li $v0, 8
	la $a0, str2
	li $a1, 64
	syscall
	

	concat:
		#$str1 first
		li $t0, 0 
		li $s1, 0 #Str3 counter
		firstLoop:
			lb $t1, str1($t0)
			beq $t1, '\n', endFirstLoop
			
			sb $t1, str3($s1)
			add $s1, $s1, 1
			add $t0, $t0, 1
						
			bne $t1, '\n' firstLoop

		endFirstLoop:
			li $t0, 0
			
		secondLoop:
			lb $t1, str2($t0)	
			beq $t1, '\n', endConcat

			sb $t1, str3($s1)
			add $s1, $s1, 1
			add $t0, $t0, 1
						
			bne $t1, '\n' secondLoop
			
		endConcat:
			#set last byte to 0
			add $s1, $s1, 1
			sb $zero, str3($s1)
	
	#Print string
	li $v0, 4
	la $a0, str3
	syscall
	
	
	li $v0, 0x0A
	syscall