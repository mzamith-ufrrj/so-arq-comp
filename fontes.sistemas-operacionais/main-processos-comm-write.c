/*
 * Representa o processo A na comunicação por memória compartilhada nomeada.
 * Cria e mapeia a região /memoria_so para armazenar um valor inteiro,
 * o identificador do processo escritor e uma mensagem de texto.
 * Aguarda ENTER para que o processo B possa ser executado separadamente
 * e então consulta os dados compartilhados novamente.
 * Ao terminar, libera o mapeamento, fecha o descritor e remove o objeto nomeado.
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
     * Cria um objeto de memória compartilhada
     * identificado pelo nome /memoria_so.
     */
    fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);

    if (fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    /*
     * Define o tamanho da região compartilhada.
     */
    if (ftruncate(fd, sizeof(MemoriaCompartilhada)) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    /*
     * Mapeia a memória compartilhada
     * no espaço de endereçamento deste processo.
     */
    MemoriaCompartilhada *mem = mmap(NULL, sizeof(MemoriaCompartilhada), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (mem == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    /*
     * Escreve dados na região compartilhada.
     */
    mem->valor = 10;
    mem->pid_escritor = getpid();

    strcpy(mem->mensagem,  "All your bases are belong to us!");

    printf("PROCESSO A\n");
    printf("PID              : %d\n", getpid());
    printf("Endereco virtual : %p\n", (void *) mem);
    printf("Valor            : %d\n", mem->valor);
    printf("Mensagem         : %s\n", mem->mensagem);

    printf("\nExecute agora o processo B.\n");
    printf("Depois pressione ENTER.\n");

    getchar();

    /*
     * Depois que o processo B alterar o valor,
     * o processo A verifica a mesma região.
     */
    printf("\nPROCESSO A consultando novamente:\n");
    printf("Valor = %d\n", mem->valor);
    printf("Mensagem = %s\n", mem->mensagem);

    munmap(mem, sizeof(MemoriaCompartilhada));
    close(fd);

    /*
     * Remove o objeto de memória compartilhada.
     */
    shm_unlink(SHM_NAME);

    return 0;
}