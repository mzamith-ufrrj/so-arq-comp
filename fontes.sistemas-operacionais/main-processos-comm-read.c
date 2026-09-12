/*
 * Representa o processo B na comunicação por memória compartilhada nomeada.
 * Abre e mapeia a região /memoria_so, previamente criada pelo processo A.
 * Exibe o valor, a mensagem e o identificador do escritor armazenados nela,
 * além do próprio identificador e do endereço virtual do mapeamento.
 * Em seguida, modifica o valor e a mensagem compartilhados e libera seus recursos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>

#define SHM_NAME "/memoria_so"

typedef struct {
    int valor;
    pid_t pid_escritor;
    char mensagem[128];
} MemoriaCompartilhada;

int main(void)
{
    int fd;

    /*
     * Abre uma região de memória compartilhada
     * que já foi criada por outro processo.
     */
    fd = shm_open(SHM_NAME, O_RDWR, 0666);

    if (fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    /*
     * Mapeia a mesma região no espaço
     * de endereçamento deste processo.
     */ 
    MemoriaCompartilhada *mem = mmap( NULL, sizeof(MemoriaCompartilhada), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (mem == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    printf("PROCESSO B\n");
    printf("PID              : %d\n", getpid());
    printf("Endereco virtual : %p\n", (void *) mem);
    printf("\nDados encontrados:\n");
    printf("PID do escritor  : %d\n", mem->pid_escritor);
    printf("Valor            : %d\n", mem->valor);
    printf("Mensagem         : %s\n", mem->mensagem);

    /*
     * Agora o segundo processo modifica
     * a região compartilhada.
     */
    mem->valor = 99;

    strcpy(mem->mensagem, "We get signal!");

    printf("\nPROCESSO B modificou a memória.\n");
    printf("Novo valor = %d\n", mem->valor);

    munmap(mem, sizeof(MemoriaCompartilhada));
    close(fd);

    return 0;
}