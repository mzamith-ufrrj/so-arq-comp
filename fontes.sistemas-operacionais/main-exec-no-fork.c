/*
 * Demonstra a execução de outro programa no processo atual usando execl(),
 * sem criar um processo filho. Após exibir uma mensagem inicial, solicita a
 * execução de ls com a opção -lh para listar o conteúdo do diretório atual.
 * O exemplo permite estudar a substituição do programa em execução e seu
 * efeito sobre a continuidade das instruções do processo.
 */

#include <stdio.h>
#include <unistd.h>
//gcc 03-main-exec-no-fork.c -o exec-nofork.exec
int main(){

    printf("\nHello");
    fflush(stdout);
    //int ret = execl("/usr/bin/htop", "htop", (char *)NULL);
    int ret = execl("/usr/bin/ls", "ls", "-lh", (char *)NULL);
    printf("\t world");
    fflush(stdout);

}
