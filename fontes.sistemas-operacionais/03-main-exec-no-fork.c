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
