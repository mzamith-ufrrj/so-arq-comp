/*
 * Implementa um terminal simples que lê comandos e argumentos, cria um
 * processo filho com fork() e solicita a execução do comando com execvp().
 * O processo pai aguarda o filho antes de receber o próximo comando.
 * Ao receber SAIR, o terminal apresenta informações sobre seu próprio
 * processo obtidas em /proc, incluindo estado, escalonamento, limites,
 * entrada e saída, mapa de memória e descritores de arquivos abertos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <limits.h>



#define BUFFER_SIZE 1024
#define MAX_ARGS 32
//gcc 02-main-fork.c -o fork-processos.exec

void imprime_arquivo(const char *titulo, const char *arquivo);
void imprime_descritores(pid_t pid);
void imprime_pcb(pid_t pid);

int main (int ac, char**av){
    char in_console[BUFFER_SIZE];
    char *arguments[MAX_ARGS];
    int index = 0;
    bool flag = true;
    printf("\n\nOlá, seja bem vindo ao terminado desenvolvido para aula de S.O.\n");
    printf("para o curso de Ciência da Cmputação da UFRRJ/IM\n");

    do{
        index = 0;
        printf("\n> ");
        fgets(in_console, BUFFER_SIZE, stdin);
        char *token = strtok(in_console, " \t\n");
        while (token != NULL) {
            arguments[index++] = token;
            token = strtok(NULL, " \t\n");
        }
        arguments[index] = NULL;
        if (strcmp(arguments[0], "SAIR") == 0){
            flag = false;
        }else{
            pid_t pid = fork();
            if (pid < 0) {
                perror("ERROR: não foi possível criar o processo");
                exit(EXIT_FAILURE);
            }else if (pid == 0){
                execvp(arguments[0], arguments);
                perror("execvp");
            }else {
                
                waitpid(pid, NULL, 0);
            }
        }
        
        
    }while (flag);
    imprime_pcb( getpid());
    printf("fim do terminal\n\n");
    return EXIT_SUCCESS;
}


void imprime_arquivo(const char *titulo, const char *arquivo)
{
    FILE *fp;
    char linha[4*BUFFER_SIZE];

    fp = fopen(arquivo, "r");

    if (fp == NULL) {
        printf("\n[%s]\n", titulo);
        printf("Não foi possível acessar %s\n", arquivo);
        return;
    }

    printf("\n==============================\n");
    printf("%s\n", titulo);
    printf("==============================\n");

    while (fgets(linha, sizeof(linha), fp) != NULL) {
        printf("%s", linha);
    }

    fclose(fp);
}


void imprime_descritores(pid_t pid)
{
    char diretorio[256];
    char caminho[PATH_MAX];
    char destino[PATH_MAX];

    DIR *dir;
    struct dirent *entrada;

    snprintf(diretorio, sizeof(diretorio), "/proc/%d/fd", pid);
    dir = opendir(diretorio);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    printf("\n==============================\n");
    printf("DESCRITORES DE ARQUIVOS\n");
    printf("==============================\n");

    while ((entrada = readdir(dir)) != NULL) {

        if (entrada->d_name[0] == '.')
            continue;

        snprintf(caminho, sizeof(caminho), "/proc/%d/fd/%s", pid, entrada->d_name);

        ssize_t tam = readlink( caminho, destino, sizeof(destino) - 1);

        if (tam != -1) {
            destino[tam] = '\0';
            printf("FD %-4s -> %s\n", entrada->d_name, destino);
        }
    }

    closedir(dir);
}


void imprime_pcb(pid_t pid)
{
    char arquivo[256];

    printf("\n\n");
    printf("########################################\n");
    printf("# VISÃO DO PROCESSO / PCB - PID %-7d #\n", pid);
    printf("########################################\n");

    snprintf(arquivo, sizeof(arquivo), "/proc/%d/status", pid);
    imprime_arquivo("STATUS DO PROCESSO", arquivo);

    snprintf(arquivo, sizeof(arquivo), "/proc/%d/stat", pid);
    imprime_arquivo("STAT DO PROCESSO", arquivo);

    snprintf(arquivo, sizeof(arquivo), "/proc/%d/sched", pid);
    imprime_arquivo("ESCALONAMENTO", arquivo);

    snprintf(arquivo, sizeof(arquivo), "/proc/%d/limits", pid);
    imprime_arquivo("LIMITES DO PROCESSO", arquivo);


    snprintf(arquivo, sizeof(arquivo),"/proc/%d/io", pid);
    imprime_arquivo("INFORMAÇÕES DE I/O",arquivo);

    snprintf(arquivo, sizeof(arquivo), "/proc/%d/maps", pid);

    imprime_arquivo( "MAPA DE MEMÓRIA",arquivo);
    imprime_descritores(pid);
}