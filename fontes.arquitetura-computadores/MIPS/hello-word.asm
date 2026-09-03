	.data	#data section

out_string:   .asciiz "Hello world!\n"
out_author:  .asciiz "Marcelo Zamith"
golden_number:       .float 0.0
	
	   .text #text segment - mips structions
	
main:
	li $v0, 4	
	la $a0, out_string
	syscall

	li $v0, 10
	syscall	
