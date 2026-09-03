#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
int main(void) {
    uint32_t a = 0xFFFFFFFF;  // maior valor de 32 bits sem sinal
    uint32_t b = 1;
    uint32_t result;

    bool overflow = __builtin_add_overflow(a, b, &result);

    if (overflow) {
        printf("Overflow detectado em unsigned!\n");
    } else {
        printf("Resultado: %u\n", result);
    }
    return EXIT_SUCCESS;
}
