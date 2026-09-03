		.data 			#Inicio da segmento de dados
		
n_value:	.word 	10 		#Variável que contém os n valores

		.text 			#Inicio do segmento de texto
main:
		la $t0, n_value        	#Copiando o valor para o registrador
		lw $a0, 0($t0)
		jal fatorial
 
		add  $a0, $v0, $zero  	#Copia do retorno da função para imprimir
		li   $v0, 1		#Setando o valor $v0 = 1 para imprimir 
					#o valor inteiro.
		syscall	
		
exit:		li $v0, 10      	#Chamada ao sistema para terminar o código
		syscall
		
fatorial:	beq  $a0, 1, end_fat   #Verifica se é 1 e retorna se for verdadeiro
		addi $sp, $sp, -8      #abre espaço na pilha
		sw   $a0, 0($sp)       #coloca na pilha
		sw   $ra, 4($sp)       #coloca na pilha
		subi $a0, $a0, 1       #subtrai 1
		jal fatorial
		lw   $ra, 4($sp)
		lw   $a0, 0($sp)
		addi $sp, $sp, 8      #abre espaço na pilha
		mul  $v0, $a0, $v0
		jr   $ra
end_fat:        li   $v0, 1
		jr   $ra			
