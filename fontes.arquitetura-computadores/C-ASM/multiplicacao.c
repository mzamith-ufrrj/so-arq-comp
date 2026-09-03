#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdint.h>

int main (void){
    uint32_t multiplicanado = 9;
    uint32_t multiplicador = 9;
    uint32_t produto = 0;
    uint32_t mascara = 0x00000001;
    uint32_t operando = 0; //produto & mascara;
    uint8_t  count = 0;

    while (count < 32){
        operando = multiplicador  & mascara ;
        operando = multiplicanado * operando;
        produto  = produto + operando;           //O error
        multiplicanado  = multiplicanado << 1;
        multiplicador   = multiplicador >> 1;
        count = count + 1;

    }


    printf("\n %u\n", produto);
    return EXIT_SUCCESS;
}
