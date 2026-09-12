/*
 * Aborda o problema dos filósofos famintos por meio de processos que
 * representam filósofos e de regiões de memória compartilhada destinadas
 * aos garfos e às informações de controle. O pai cria os filhos, utiliza
 * sinais para despertá-los e aguarda seu encerramento. As atividades de
 * pensar e comer compõem o cenário para estudar concorrência e o uso de
 * recursos compartilhados entre processos.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#define PROCESS 3
#define STEPS 10
#define ELAPSED_TIME 10 * 1000000

void handler(int sig){
    fprintf(stdout, "Eu sou o filósofo %d. Acabei de acordar!\n", getpid());
    fflush(stdout);
}

void thinking( uint64_t whoAmI){
    fprintf(stdout, "Eu sou o filósofo %u. Estou pensando!\n", whoAmI);
    fflush(stdout);
}


void eating(uint64_t whoAmI, uint64_t n_process, pthread_mutex_t *forks){
    fprintf(stdout, "Eu sou o filósofo %u. Estou comendo com os garfos (%u, %u)!\n", whoAmI, whoAmI, (whoAmI + 1) % n_process);
    fflush(stdout);
}

int main(int ac, char **av)
{
    pthread_mutex_t     *forks = NULL;          /* O mutex representa os garfos. Para N filosofos há N garfos. */
    pthread_mutexattr_t *attr   = NULL;
    int *philosopher = NULL;
    uint64_t whoAmI = 0;
    uint64_t n_proccess = PROCESS;
    uint64_t n_steps = STEPS;

    int32_t     root = getpid();

    printf("\nSistemas Operacionais: Processos - Exemplo \n");
    printf("\t - Filósofos famintos %d.\n", getpid());
    fflush(stdout);

    forks  = mmap(NULL, n_proccess * sizeof(pthread_mutex_t), PROT_READ | PROT_WRITE,  MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    assert(forks != MAP_FAILED);

    attr = mmap(NULL, n_proccess * sizeof(pthread_mutexattr_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    assert(attr != MAP_FAILED);

    philosopher = mmap(NULL, n_proccess * sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    assert(philosopher != MAP_FAILED);


    for (uint64_t i = 0; i < n_proccess; i++){
        pid_t pid = fork();
        assert(pid >= 0);
        
        if (pid == 0){//Filho
            whoAmI = i;
            signal(SIGUSR1, handler);
            pause(); //Coloca o processo em espera
            i = n_proccess + 1;
        }else{
            philosopher[i] = (int) pid;
        }
    }

    if (root != getpid()){

        bool running = true;
        uint64_t count = 0;
        while(running){
            thinking(whoAmI);    
            if (eating(whoAmI, n_proccess, forks))
                count++;
            if (count == n_steps)
                running = false;
        }
        
    }
    


    if (root == getpid()){
        fprintf(stdout, "Se chegou até aqui, então é o processo pai %d\n", getpid());
        fprintf(stdout, "Vamos aguardar uns segundos....\n");
        fflush(stdout);
        usleep(ELAPSED_TIME);
        for (uint64_t i = 0; i < n_proccess; i++) {
                kill(philosopher[i], SIGUSR1); //Acorda os processos filhos
        }


        for (uint64_t i = 0; i < n_proccess; i++) {
            waitpid(philosopher[i], NULL, 0); //Espera os processos filhos terminarem
        }

        printf("\n\n");
    }

    
    fflush(stdout);
    munmap(forks, n_proccess * sizeof(pthread_mutex_t));
    munmap(attr, n_proccess * sizeof(pthread_mutexattr_t));
    munmap(philosopher, n_proccess * sizeof(int));
    return EXIT_SUCCESS;
}
