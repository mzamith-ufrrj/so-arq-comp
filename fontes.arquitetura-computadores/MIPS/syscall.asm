	.data
	
string1: .asciiz "Marcelo Zamith"
string2: .asciiz "Bom dia,"
string3: .asciiz "Seja bem vindo"

	.text
main:
	li $v0, 4         #Load Immadiate
	la $a0, string2   #Load address
	syscall

	
	li $v0, 4
	la $a0, string1
	syscall

	li $v0, 11
	li $a0, '\n'
	syscall

	li $v0, 4
	la $a0, string3
	syscall