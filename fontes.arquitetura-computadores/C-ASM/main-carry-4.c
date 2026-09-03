#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main() {
    uint64_t a = 0xFFFFFFFFFFFFFF00;


    unsigned char carry;

    do{
        printf("\t --> %x\n", a);
        a++;

        __asm__ (
            "setc %0"       // seta %0 com o OF (overflow flag)
            : "=r"(carry)
            :
            : "cc"
        );

    }while (!carry);


    return EXIT_SUCCESS;
}
