        .data
    
txt1:   .asciiz "12345"
txt2:   .asciiz "Teste"

        .text
    
main:

    la $a0, txt1
    la $a1, txt2
    jal strcpy
    
    li $v0, 10
    syscall

strcpy:
	addi $sp, $sp, -4  # ajusta a pilha para mais 1 item
	sw   $s0, 0($sp)   # salva $s0
	
	add  $s0, $zero, $zero   # inicializa  i=0
	
L1:	#while
	add $t1, $s0, $a1     # endereço de y[i] em $t1
	lbu $t2, 0($t1)  # $t2 = y[i]
	add $t3, $s0, $a0     # endereço de x[i] em $t3
	sb  $t2, 0($t3)  # x[i] = y[i]
	
	beq $t2, $zero, L2  # se y[i] == 0, vai para L2
	addi $s0, $s0, 1   # i = i + 1
	j  L1
	
L2:	#fim while
	lw $s0, 0($sp)  # restaura $s0 antigo
	addi $sp, $sp, 4  #ajusta $sp
	
	jr $ra  # retorna para chamador