		.data 		#Inicio da segmento de dados
		
n_value:	.word 	10 	#Variável que contém os n valores

		.text 		#Inicio do segmento de texto
main:
		li $v0, 1
		la $t0, n_value	#registador aponta para a variável
		lw $a0, 0($t0)	#copia dados da variável para o registrador $a0
		jal fibonacci
		syscall	
		
exit:		li $v0, 10      #Chamada ao sistema para terminar o código
		syscall
		
fibonacci:
		li $v0, 1
		la $t0, n_value
		lw $a0, 0($t0)
		addi $a0, $a0, 2
		syscall
		jr $ra			