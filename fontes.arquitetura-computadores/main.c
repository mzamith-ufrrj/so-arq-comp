#include <stdio.h>
int main (){
    int vet[32];
    vet[0] = 1;
    vet[1] = 2;
    vet[2] = 3;
    int *ptr = &vet[0];

    printf("\n");
    printf("%d %d %d", vet[0], vet[1], vet[2]);
    printf("\n");

    printf("%d %p\n", *ptr, ptr);ptr++;
    printf("%d %p\n", *ptr, ptr);ptr++;
    printf("%d %p\n", *ptr, ptr);
    printf("\n");

    return 0;
}
