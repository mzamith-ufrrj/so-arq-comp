/*
 * Aborda o problema do produtor e consumidor com dois processos: o pai
 * representa o produtor e o filho representa o consumidor. Ambos acessam
 * um vetor em memória compartilhada, no qual a produção e o consumo são
 * representados por alterações nos valores das posições. O programa usa
 * um mutex compartilhado entre processos nas regiões críticas e exibe o
 * estado do vetor durante as operações, permitindo estudar sua coordenação.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <assert.h>
#include <string.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#define ELAPSED_TIME 3 * 1000000
#define FATHER 0
#define CHILD  1

typedef struct{
    uint64_t *vet;
    uint64_t steps;
    uint64_t f; //aponta para o primeiro elemento
    uint64_t l; //aponta para o último elemento
    uint64_t N; //Tamanho da amostra
}tpDate;

typedef struct{
    pthread_mutexattr_t    attr;
    pthread_mutex_t        mutex;
}tpCtrl;

void print(tpDate *date){
    printf("\t\t-----------------------------\n\t\t  ");
    for (uint64_t i = 0; i < date->N; i++)
        printf("%u ", date->vet[i]);
    printf("\n\t\t - F: %u\n", date->f);
    printf("\t\t - L: %u\n", date->l);
    printf("\t\t - N: %u\n", date->N);
    printf("\t\t-----------------------------\n");

}

void producer(tpDate *date, tpCtrl *ctrl){
    
    bool running = true;
    uint64_t i = 0;
    while (running){
            /*
            * Região crítica - produtor
            */

            pthread_mutex_lock(&ctrl->mutex);
                fprintf(stdout, "\t\t - Start producer %u\n", i);
                fflush(stdout);

                uint64_t index = 0;
                while (index < date->N){

                    //ERROR:
                    if (date->vet[date->l] == 1){
                        fprintf(stderr, "[ERROR PRODUCER]:\n");
                        print(date);        
                    }
                    assert(date->vet[date->l] == 0);
                    
                    date->vet[date->l] = 1;
                    index++;
                    if (index < date->N){
                        date->l++;
                        if (date->l == date->N) date->l = 0;
                    }
                }
                print(date);
                fprintf(stdout, "\t\t - End producer\n");
                fflush(stdout);
                if (i == date->steps) running = false;
                else i++;
            pthread_mutex_unlock(&ctrl->mutex);
         
    }   

}

void consumer(tpDate *date, tpCtrl *ctrl){
   
    bool running = true;
    uint64_t i = 0;
    while (running){
         
            /*
             * Região crítica - consumidor
             */
            pthread_mutex_lock(&ctrl->mutex);
                fprintf(stdout, "\t\t - Start consumer %u\n", i);
                fflush(stdout);

                uint64_t index = 0;
                

                while (index < date->N){
                    //ERROR:
                    if (date->vet[date->f] == 0){
                        fprintf(stderr, "[ERROR CONSUMER]:\n");
                        print(date);        
                    }
                    assert(date->vet[date->f] == 1);
                    date->vet[date->f] = 0;
                    index++;
                    if (index < date->N){
                        date->f++;
                        if (date->f == date->N) date->f = 0;
                    }
                }
                print(date);
                fprintf(stdout, "\t\t - End consumer\n");
                fflush(stdout); 
                if (i == date->steps) running = false;
                else i++;
            pthread_mutex_unlock(&ctrl->mutex);
        
    }
}


int main(int ac, char **av)
{
     
    tpDate *date = NULL;
    tpCtrl *ctrl = NULL;

    printf("\nSistemas Operacionais: Processos - Exemplo \n");
    printf("\t - 1 produtor x 1 consumidor %d.\n", getpid());
    fflush(stdout);

    ctrl  = mmap(NULL, sizeof(tpCtrl), PROT_READ | PROT_WRITE,  MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    assert(ctrl != MAP_FAILED);
    
    date = mmap(NULL, sizeof(tpDate), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    assert(date != MAP_FAILED);

   
    date->steps = 100000;
    date->N = 10;
    date->f = 0;
    date->l = 0;
   
    date->vet = mmap(NULL, date->N * sizeof(uint64_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    assert(date->vet != MAP_FAILED);
    bzero(date->vet, sizeof(uint64_t) * date->N);

 


    pthread_mutexattr_init(&ctrl->attr);
    pthread_mutexattr_setpshared(&ctrl->attr, PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(&ctrl->mutex, &ctrl->attr);
    
    pid_t pid = fork();
    assert(pid >= 0);

    if (pid == 0){//Filho
        printf("\t\t\tProcesso filho %d\n", pid);
        consumer(date, ctrl);
        munmap(date->vet, sizeof(uint64_t) * date->N);
        munmap(date, sizeof(date));
        munmap(ctrl, sizeof(ctrl));

    }else{//Pai
        printf("\t\t - Processo PAI %d\n", pid);
        producer(date, ctrl);
        fprintf(stdout, " Aguardando o processo filho terminar!\n");
        fflush(stdout);
        wait(NULL);
        
        pthread_mutex_destroy(&ctrl->mutex);
        pthread_mutexattr_destroy(&ctrl->attr);
      

        munmap(date->vet, sizeof(uint64_t) * date->N);
        munmap(date, sizeof(date));
        munmap(ctrl, sizeof(ctrl));
        

    }
    
    



    //free(date->vet);
    //free(date);
    //free(ctrl);

    printf("\n\n");
    return EXIT_SUCCESS;
}
