#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>
int main (int ac, char**av){
    printf("\nOlá, eu sou o processo %d e estou em loop infinito\n", getpid());
    int i = 0;
    //Mantém em loop infinito para matar com comando KILL
    while(true){
        i++;
        i %= 8192;
    }
    return EXIT_SUCCESS;
}