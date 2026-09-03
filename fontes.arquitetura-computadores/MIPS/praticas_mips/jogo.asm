.data
random_seed:    .word   0
secret_number:  .word   0
guess:          .word   0
# Strings
prompt:     .asciiz "Adivinhe o número (1-100): "
too_low:    .asciiz "Muito baixo! Tente novamente.\n"
too_high:   .asciiz "Muito alto! Tente novamente.\n"
win_message: .asciiz "Parabéns! Você adivinhou o número secreto!\n"

.text
.globl main

main:
    # Pegando o relogio
    li $v0, 30
    syscall

    # Inicialize a semente para a geração de números aleatórios
    li $v0, 40       # Código de serviço 42 para inicializar a semente
    add $a1, $zero, $a0        # Semente = relogio
    syscall

    # Gere o número secreto aleatório entre 1 e 100
    li $v0, 42       # Código de serviço 42 para gerar um número aleatório
    #li $a0, 0        # seed
    li $a1, 100      # Máximo valor aleatório
    syscall
    addi $a1, $zero, 1   # Mínimo valor aleatório (1)
    sw $a0, secret_number

game_loop:
    # Solicite ao jogador que insira sua tentativa
    li $v0, 4
    la $a0, prompt
    syscall

    # Leia a tentativa do jogador
    li $v0, 5
    syscall
    sw $v0, guess

    # Compare a tentativa com o número secreto
    lw $t0, secret_number
    lw $t1, guess
    beq $t1, $t0, player_wins
    bge $t1, $t0, guess_too_high

    # A tentativa é menor do que o número secreto
    li $v0, 4
    la $a0, too_low
    syscall
    j game_loop

guess_too_high:
    # A tentativa é maior do que o número secreto
    li $v0, 4
    la $a0, too_high
    syscall
    j game_loop

player_wins:
    # O jogador adivinhou corretamente
    li $v0, 4
    la $a0, win_message
    syscall

    # Encerre o programa
    li $v0, 10
    syscall


