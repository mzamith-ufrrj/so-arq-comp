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
