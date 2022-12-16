# Trabalho Pratico Final SSC0902-2021
# Francisco Reis Nogueira
# Nusp: 11954374
# Email: fr.nogueira<at>usp.br
			
	.data	
# Caminhos arquivos
imageFile: .asciiz "imagem.pgm"
outputFile: .asciiz "imgproc.pgm"

# Buffers
header: .space 38
byteRead: .space 1

# Vetor Histograma
histograma: .space 256

# Strings
newline: .asciiz "\n"
openBrackets: .asciiz " ( "
closeBrackets: .asciiz " ) "
colon: .asciiz " : "

# Defines
high: .byte 255
low: .byte 0
imageSize: .word 10000

	.text
.globl main

main:

	#################################### (1) (2) (3) ####################################

	# Abrir o arquivo de Input
	la $a0, imageFile 	# Param: nome arquivo -> Input
	li $a1, 0 		# Param: Abrir arquivo para leitura (0: read, 1: write)
	li $a2, 0 		# Param: Ignorar modo
	jal openFile		# Funcao de abrir o arquivo
	move $s6 $v0		#Salvar o file descriptor em $s6
	
	# Abrir o arquivo Output
	la $a0, outputFile 	# Param: nome arquivo -> Output
	li $a1, 1 		# Param: Abrir arquivo para escrita (0: read, 1: write)
	li $a2, 0 		# Param: Ignorar modo
	jal openFile		# Funcao abrir arquivo
	move $s5 $v0		# Salvar o file descriptor em $s5	
	
	# Ler o cabecalho do arquivo input
	move $a0, $s6		# Param: $s6 sera o file descriptor
	la $a1, header		# Param: Passar o header como buffer
	li $a2, 38		# Param: Tamanho do header
	jal readFromFile	# Ler do arquivo de acordo com os parametros

	
	# Escrever o header no arquivo output
	move $a0, $s5		# Param: definir o file descriptor para escrita
	la $a1, header		# Param: Buffer de escrita
	li $a2, 38		# Param: Quantidade de bytes para escrever
	jal writeAtFile		# Escrever no arquivo
	
	
	# Loop para ler o resto do arquivo
	lw $t7, imageSize 	# $t7 guarda o tamanho da imagem
	addi $t1, $zero, 0	# Counter para o Loop
	readingLoop:
		# Ler um unico byte do arquivo
		move $a0, $s6			# Param: File descriptor
		la $a1, byteRead		# Param: Buffer de leitura
		li $a2, 1			# Param: Tamanho do buffer
		jal readFromFile		# Ler do arquivo
		
		# Adicionar byte correspondente no vetor histograma
		# Multiplicar o byte por 4 -> Lugar correspondente no vetor
		# i.e. Leu 16 -> histograma[16]++
		lbu $t5, byteRead		# Ler byte unsigned
				
		# Incrementar na posicao $t5
		lb $t2, histograma($t5)		# Ler quantidade atual do vetor
		addi $t2, $t2, 1		# Incrementar quantidade
		sb $t2, histograma($t5)		# Salvar o novo valor no vetor
				
		
		add $t1, $t1, 1 		# i++
		blt $t1, $t7, readingLoop 	# i<imagesize
	
	# Imprimir o Histograma
	jal printFullHistogram	# Imprimir o Histograma

	#################################### (1) (2) (3) ####################################
	
	####################################   (4) (5)   ####################################

	# Reler o arquivo input para escrever o arquivo output de acordo com o Threshold
	# O arquivo esta sendo reaberto para voltar o file descriptor no comeco do arquivo.
	move $a0, $s6		# Param: File descriptor para fechar o arquivo
	jal closeFile		# Fechar o arquivo input
	
	# Abrir o arquivo de Input
	la $a0, imageFile 	# Param: nome arquivo -> Input
	li $a1, 0 		# Param: Abrir arquivo para leitura (0: read, 1: write)
	li $a2, 0 		# Param: Ignorar modo
	jal openFile		# Funcao de abrir o arquivo
	move $s6 $v0		#Salvar o file descriptor em $s6
	
	# Ler o cabecalho do arquivo input
	move $a0, $s6		# Param: $s6 file descriptor
	la $a1, header		# Param: Passar o header como buffer
	li $a2, 38		# Param: Tamanho do header
	jal readFromFile	# Ler do arquivo de acordo com os parametros
	
	
	# Ler o limite do usuario
	li $v0, 5		# Ler o limite do usuario
	syscall
	move $s1, $v0		# Limite salvo em $s1
	
	# Fazer um outro loop para escrever o arquivo output
	lw $t7, imageSize	# $t7 recebe o tamanho da imagem
	addi $t1, $zero, 0	# Counter
	
	writeImageLoop:	
		# Ler um unico byte do arquivo
		move $a0, $s6			# Param: File descriptor
		la $a1, byteRead		# Param: Buffer de leitura
		li $a2, 1			# Param: Tamanho do buffer
		jal readFromFile		# Ler do arquivo
		
		
		# Verificar o threshold	
		lbu $a1, byteRead		# Pegar o valor byte unsigned
		blt $a1, $s1, setBelowThreshold # if valorLido < threshold
		
		# Setar para branco (High)
		setAboveThreshold:
			la $a1, high		# Setar o byte para branco
			j writeImage		# Escrevevr no output
		
		# Setar para preto (Low)
		setBelowThreshold:
			la $a1, low		# Setar o byte para preto
			j writeImage		# Escrever no output
			
		# Escrever no output
		writeImage:
			move $a0, $s5		# Param: File descriptor
			li $a2, 1		# Param: Tamanho para escrever (1 byte)
			jal writeAtFile		# Escrever no arquivo
	
		add $t1, $t1, 1 		# i++
		blt $t1, $t7, writeImageLoop	# i<imagesize
	
	# Fechar o arquivo Input
	move $a0, $s6		# Param: File descriptor do Input
	jal closeFile		# Fechar o arquivo
	
	# Fechar o arquivo Output
	move $a0, $s5		# Param: File descriptor do Output
	jal closeFile		# Fechar o arquivo
	
	# Sair do programa
	j exit			# Sair do programa

	####################################   (4) (5)   ####################################


# Sub rotina para print do histograma
printFullHistogram:
	li $t1, 256		# Tamanho do Histograma
	li $t2, 0		# Counter
	sw $ra, 0($sp)		# Salvar o $ra no topo da stack
	
	# Loop de print
	printHistLoop:
		# Pegar a posicao atual do counter no array
		lbu $t4, histograma($t2)	# Ler do Histograma e guardar em $t4
		
		# Print (
		la $a0, openBrackets		# Param: (
		jal printString			# Print string (
		
		# Print Counter
		move $a0, $t2			# Param: valor do counter	
		jal printInteger		# Print integer counter
		
		# Print :
		la $a0, colon			# Param: :
		jal printString			# Print string: :
		
		# Print valor do Histograma
		move $a0, $t4			# Param: valor do histograma
		jal printInteger		# Print integer counter

		# Print closeBrackets
		la $a0, closeBrackets		# Param: )
		jal printString			# Print string )
		
		add $t2, $t2, 1			# i++
		blt $t2, $t1, printHistLoop	# i < tamHistograma
		
	# Print nova linha
	la $a0, newline		# Param: "\n"
	jal printString		# Print nova linha
	
	# Pegar o $ra da stack
	lw $ra, 0($sp)		# POP stack pointer
	jr $ra			# Sair da subrotina

# Sub rotina para print de uma string
# Parametros em $a0
printString:
	li $v0, 4 		# Syscall para print de string
	syscall
	jr $ra			# Sair da subrotina
	
# Sub rotina para print de um integer
# Parametros em $a0
printInteger:
	li $v0, 1		# Syscall para print de integer
	syscall
	jr $ra			# Sair da subrotina

# Escrever valor em um arquivo
# $a0: File descriptor
# $a1: Buffer com os valores que serao escritos
# $a2: Tamanho do buffer
writeAtFile:
	li $v0, 15		# Syscall para escrita em um arquivo
	syscall
	jr $ra			# Sair da subrotina


# Ler valor de um arquivo
# $a0: File descriptor
# $a1: Buffer no qual sera guardado os valores lidos
# $a2: Quantidade de bytes para leitura
readFromFile: #Ler um arquivo
	li $v0, 14		# Syscall para ler de um arquivo
	syscall
	jr $ra			# Sair da subrotina


# Abrir um arquivo
# $a0: Nome do arquivo para ser aberto
# $a1: Flags de abertura ( 0: Ler, 1: Escrever )
# $a2: Modo de abertura ( Nao utilizado )
openFile: #Abrir um arquivo
	li $v0, 13 		# Syscall para abrir o arquivo
	syscall			# Abrir arquivo -> Salvo em $v0
	jr $ra			# Sair da subrotina

# Fechar um arquivo
# $a0: File descriptor
closeFile: 
	li $v0, 16		# Syscall para fechar arquivo
	syscall			# Fechar arquivo
	jr $ra			# Sair da subrotina
	
# Sair do programa
exit:
	li $v0, 0x0A		# Syscall para sair do programa
	syscall

