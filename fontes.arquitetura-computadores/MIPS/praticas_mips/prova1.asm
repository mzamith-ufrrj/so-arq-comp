Main:
    addi $a0, $zero, 3
    jal Proc
    
Proc:
    addi $sp, $sp, -4
    sw $s0, 0($sp)

    add $s0, $zero, $a0
    add $t0, $zero, $a0
    add $v0, $zero, $zero
Loop:
    add $v0, $v0, $s0
    addi $t0, $t0, -1
    bne $t0, $zero, Loop

    lw $s0, 0($sp)
    addi $sp, $sp, 4

    jr $ra