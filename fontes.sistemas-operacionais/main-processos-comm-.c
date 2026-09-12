/*
 * Demonstra a comunicação entre pai e filho por uma região de memória
 * compartilhada, criada com mmap antes da chamada a fork.
 * O filho consulta o valor inicial e altera o inteiro armazenado nessa região.
 * O pai aguarda o término do filho e exibe o valor após a alteração.
 * As saídas mostram os identificadores dos processos e o endereço da região.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main(void)
{
    int *memoria_compartilhada = NULL;

    /*
     * Cria uma região de memória compartilhada.
     */
    memoria_compartilhada = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (memoria_compartilhada == MAP_FAILED) {perror("mmap");exit(EXIT_FAILURE);}

    *memoria_compartilhada = 10;

    printf("Antes do fork:\n");
    printf("PID = %d | valor = %d | endereco = %p\n", getpid(), *memoria_compartilhada, (void *) memoria_compartilhada);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        /* Processo filho */
        printf("\nFILHO\n");
        printf("PID = %d\n", getpid());
        printf("PPID = %d\n", getppid());
        printf("Valor recebido = %d\n", *memoria_compartilhada);
        printf("Endereco = %p\n", (void *) memoria_compartilhada);
        /*
         * Filho modifica a memória compartilhada.
         */
        *memoria_compartilhada = 50;
        printf("Filho alterou valor para %d\n",*memoria_compartilhada);
        munmap(memoria_compartilhada, sizeof(int));

        exit(EXIT_SUCCESS);
    }

    else {
        /* Processo pai */
        wait(NULL);
        printf("\nPAI\n");
        printf("PID = %d\n", getpid());
        printf("Valor depois da execução do filho = %d\n",*memoria_compartilhada);
        printf("Endereco = %p\n",(void *) memoria_compartilhada);
        munmap(memoria_compartilhada, sizeof(int));
    }

    return EXIT_SUCCESS;
}