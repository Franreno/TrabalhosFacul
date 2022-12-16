# Lista encadeada com alocacao dinamica

	.data
Vetor:  .word 15, 31, 63, 127, 255, 511, 1023, 2047, 4097, 65536, 0
lista:  .word 0
qntNos: .byte 0

	.text
.globl main
main:
	la $s0, Vetor # Guarda endereco do vetor
	la $s1, lista # Guarda endereco da lista
	
	# Pegar valores do vetor
	mainLoop:
		lw $t0, ($s0)
		
		beqz $t0, printList
		
		li $v0, 9 # Sbrk
		li $a0, 8 # Alocar 8 bytes
		syscall
		
		# $v0 contem o endereco da memoria alocada
		sw $t0, ($v0) # Guardar o valor lido do vetor no endereco alocado
		sw $v0, ($s1) # Guardar o endereco alocado na lista de alocados
		la $s1, +4($v0) # Vai para o proximo lugar da lista
		
		
		# Incrementar contador
		addi $s0, $s0, 4
		
		
		# Aumentar quantidade de nos
		lb $t2, qntNos
		add $t2, $t2, 1
		sb $t2, qntNos
		
		j mainLoop
		
	printList:
		lw $s1, lista # $s0 recebe o endereco do primeiro no
		lb $t2, qntNos # $t2 guarda a quantidade de nos
		
		printLoop:
			# Print(*s0)
			li $v0, 1
			lw $a0, ($s1)
			syscall
			
			# Print(' ')
			li $v0, 11
			li $a0, ' '
			syscall
			
			# Vai para o proxEndereco
			add $s1, $s1, 4
			lw $s1, ($s1)
			
			sub $t2, $t2, 1
			bnez $t2, printLoop
			
	exit:
		li $v0, 0x0A
		syscall