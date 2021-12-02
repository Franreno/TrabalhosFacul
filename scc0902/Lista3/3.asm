	.data
dado1: .float 12345.12345
dado2: .float 11111.22222
soma:  .float 00000.00000

	.text
.globl main

main:
	l.s $f1, soma
	l.s $f2, dado1
	add.s $f1, $f1, $f2
	l.s $f2, dado2
	add.s $f1, $f1, $f2
	s.s $f1, soma
	
	li $v0, 2
	l.s $f12, soma
	syscall
	
	li $v0, 0x0A
	syscall
