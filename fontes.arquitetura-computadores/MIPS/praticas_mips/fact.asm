main:
	addi $a0, $zero, 3
	jal fact
	move $s0, $v0
	
	li $v0, 10
	syscall


fact:
	addi $sp, $sp, -8  #ajusta a pilha
	sw $ra, 4($sp)     #salva endereço de retorno
	sw $a0, 0($sp)     #salva argumento n

	slti $t0, $a0, 1    # testa se n < 1
	beq $t0, $zero, Else  #se n>=1, vai para Else

	addi $v0, $zero, 1  #retorna 1
	addi $sp, $sp, 8    #retira 2 itens da pilha
	jr $ra

Else:
	addi $a0, $a0, -1  # coloca n-1 no argumento
	jal fact           # chama fact(n-1)

	lw $a0, 0($sp)    #restaura argumento n
	lw $ra, 4($sp)    #restaura end. de retorno
	addi $sp, $sp, 8  #retira os dois itens da pilha

	mul $v0, $a0, $v0  #retorna n*fact(n-1)

	jr $ra  #retorna para quem chamou
