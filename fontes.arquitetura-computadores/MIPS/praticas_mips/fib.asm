.data
n:	.word	0
pedido: .asciiz "Digite um número: "
resposta: .asciiz "O resultado é "

.text
main:
	# imprime a mensagem de pedido
	li $v0, 4
	la $a0, pedido
	syscall
	
	# lê valor do terminal
	li $v0, 5
	syscall
	sw $v0, n
	
	# chama o procedimento fib
	lw $a0, n
	jal fib
	move $t0, $v0
	
	# imprime mensagem de resposta
	li $v0, 4
	la $a0, resposta
	syscall

	# imprime valor de resultado
	li $v0, 1
	move $a0, $t0
	syscall
	
	# exit
	li $v0, 10
	syscall
	
fib:
	#salvar na pilha
	addi $sp, $sp, -16
	sw $s0, 12($sp)
	sw $s1, 8($sp)
	sw $a0, 4($sp)
	sw $ra, 0($sp)
	
	# teste se igual a zero
	bne $zero, $a0, teste1
	li $v0, 0
	j saida
	
teste1:
	# teste se igual a um
	bne $a0, 1, teste2
	li $v0, 1
	j saida

teste2:
	#calcular fib(n-1)
	addi $a0, $a0, -1
	jal fib
	move $s0, $v0
	
	#calcular fib(n-2)
	addi $a0, $a0, -1
	jal fib
	move $s1, $v0
	
	add $v0, $s0, $s1
saida:
	#desempilhar
	lw $s0, 12($sp)
	lw $s1, 8($sp)
	lw $a0, 4($sp)
	lw $ra, 0($sp)
 	addi $sp, $sp, 16
 	
 	jr $ra