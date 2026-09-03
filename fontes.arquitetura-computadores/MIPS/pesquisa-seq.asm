		.data 			#Inicio da segmento de dados

my_vet:         .space 	64          	#Reserva 64 bytes = 16 x 4 
string_found:  	.asciiz "Achou na posicao: "
string_nfound:	.asciiz "Nao achou!"

		.text 			#Inicio do segmento de texto
main:
		add   $t0, $zero, $zero #Inicializa $t0 com 0 - índice do vetor
		la    $t1, my_vet       #load address - base do vetor
		addi  $t2, $zero, 1 	#Inicializa $t2 com 1 - palavra que vai ser gravada no vetor
		addi  $t5, $zero, 0
		
		
loop1:		add   $t3, $t1, $t5   	 #Endereco do elemento
           	sw    $t2, 0($t3)      	 #Armazena valor de $t2 no vetor (end. $t3)	
		addi  $t2, $t2, 1     	 #Incrementa $t2
		addi  $t5, $t5, 4     	 #Incrementa $t5 (multiplo de 4)
		slti  $t4, $t5, 64    	 #Verifica se chegou no fim do vetor 64 = 16 * 4
		bne   $t4, $zero, loop1  #Senão chegou, então volta e continua preenchendo 
					 #Parâmetros de entrada da função
		add   $a0, $t1, $zero    #Endereço base do vetor
		addi  $a1, $zero, 5      #elemento a ser pesquisado
		jal   pes_seq
		beq   $v0, $zero, not_found #senão achou então imprimi msg  
		li    $v0, 4       	#Imprime a msg que achou
		la    $a0, string_found
		syscall
		li    $v0, 1		#Imprime a posição do vetor
		add   $a0, $v1, $zero
		syscall
		j     exit
			
not_found:	li    $v0, 4
		la    $a0, string_nfound
		syscall
				
exit:		li $v0, 10      	#Chamada ao sistema para terminar o código
		syscall

pes_seq:	addi  $t2, $zero, 0    	   #Endereço com o índice do vetor
		addi  $t6, $zero, 0
loop2:          slti  $t4, $t6, 16         #Verifica se o vetor terminou
		beq   $t4, $zero, end_nf   #Se $t4 é igual ao tamanho vetor, então termina
		                           #e não achou...
		add   $t3, $a0, $t2        #Calcula o endereço da posição do vetor
		lw    $t5, 0($t3)          #Carrega a palavra do vetor
		beq   $t5, $a1, end_f      #achou o elemento, sai e retorna a posição
		addi  $t6, $t6, 1          #Incrementa o índice
		sll   $t2, $t6, 2          #Coloca o índice multiplo de 4 (deslocamento)
		j     loop2
			
					
end_nf:     	li   $v0, 0
		jr   $ra
		
end_f:          li   $v0, 1	
		add  $v1, $t6, $zero 	
end_seq:        jr   $ra 		
		
