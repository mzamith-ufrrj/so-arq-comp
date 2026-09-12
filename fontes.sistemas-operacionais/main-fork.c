/*
 * Apresenta a criação de um processo filho por meio de fork(). O processo
 * original exibe seu identificador e, após a criação, pai e filho seguem
 * caminhos distintos conforme o retorno dessa chamada. As mensagens mostram
 * os identificadores dos processos e a relação de parentesco entre eles,
 * utilizando getpid() e getppid().
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
//gcc 02-main-fork.c -o fork-processos.exec
int main (int ac, char**av){
    printf("\nOlá, eu sou o processo %d\n", getpid());
    pid_t pid = fork();

    if (pid < 0){
        perror("Error ao criar o processo...");
        exit(EXIT_FAILURE);
    }
    
    if (pid == 0) {
        
        printf("\t\tSou o filho. Meu PID = %d\n", getpid());
        printf("\t\tPID do meu pai = %d\n", getppid());
    } else {
        
        printf("\tSou o pai. Meu PID = %d\n", getpid());
        printf("\tPID do meu filho = %d\n", pid);
    }

    

    return EXIT_SUCCESS;
}