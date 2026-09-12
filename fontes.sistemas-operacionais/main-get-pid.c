/*
 * Explora a identificação e a criação repetida de processos. Inicialmente,
 * exibe o PID do processo em execução e o PID de seu pai. Em seguida, cada
 * processo permanece em um laço que aguarda um segundo, mostra seu próprio
 * identificador e chama fork(), fazendo com que os novos processos também
 * participem das próximas iterações.
 */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(int av, char**ac){
    pid_t parent_pid = getppid();

    printf("Hello world!, My process PID = %d / Parent pid  %d \n",getpid(), parent_pid);
    while (1){
        sleep(1);
        printf("PID = %d  \n",getpid());
        pid_t p = fork();
        if(p<0){
            perror("fork fail");
            exit(1);
        }
    }
    return 0;
}
