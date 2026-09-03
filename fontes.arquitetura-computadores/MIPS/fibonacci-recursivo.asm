		.text 			#Inicio do segmento de texto
main:
		add  $a0, $zero, $zero
		addi $a1, $zero, 1
		addi $a2, $zero, 3
		jal fib
 
		add  $a0, $v0, $zero  	#Copia do retorno da função para imprimir
		li   $v0, 1		#Setando o valor $v0 = 1 para imprimir 
					#o valor inteiro.
		syscall	
		
exit:		li $v0, 10      	#Chamada ao sistema para terminar o código
		syscall

fib:		addi $t0, $zero, 1
		beq  $a2, $t0, fib_end
		add  $v0, $a0, $a1
		#Coloca da pilha
		addi $sp, $sp, -4      #Apenas dois registradores, 1 com o resultado da soma e outro com o tamanho da pilha
		sw   $ra, 0($sp)
		add  $a0, $a1, $zero
		add  $a1, $v0, $zero
		addi $a2, $a2, -1
		jal  fib
		lw   $ra, 0($sp)
		addi $sp, $sp, 4
		jr   $ra

fib_end:        add  $v0, $a0, $a1
		jr   $ra

