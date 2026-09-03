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