#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
int main() {
    uint32_t a = 0xFFFFFFFF;
    uint32_t b = 1;
    uint32_t result;
    //unsigned char carry;
    bool carry;
    __asm__ (
        "addl %[b], %[a]\n\t"   // soma
        "setc %[cf]\n\t"        // CF -> carry flag (unsigned overflow)
        : [a] "=r"(result), [cf] "=r"(carry)
        : "0"(a), [b] "r"(b)
        : "cc"
    );

    if (carry)
        printf("Unsigned overflow detectado!\n");
    else
        printf("Resultado: %u\n", result);

    return EXIT_SUCCESS;;
}
