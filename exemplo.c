/*Gabriel Zagury 2210912 3WB*/
/*Luiza Marcondes 2210275 3WA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"

#define BIGINT_SIZE NUM_BITS / 8

#define assertBigInt(esperado, atual)                      \
    do                                                     \
    {                                                      \
        const unsigned char *esperado_arr = (esperado);    \
        const unsigned char *atual_arr = (atual);          \
        if (memcmp(esperado_arr, atual_arr, 16) != 0)      \
        {                                                  \
            fprintf(stderr, "Assert falhou: esperado ");   \
            for (int i = 15; i >= 0; i--)                  \
            {                                              \
                fprintf(stderr, "%02x", esperado_arr[i]);  \
            }                                              \
            fprintf(stderr, ", mas recebeu ");             \
            for (int i = 15; i >= 0; i--)                  \
            {                                              \
                fprintf(stderr, "%02x", atual_arr[i]);     \
            }                                              \
            fprintf(stderr, "\tNA LINHA: %d\n", __LINE__); \
            exit(1);                                       \
        }                                                  \
    } while (0)

int main(void)
{
    BigInt bigNUMNEG = {0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    BigInt bigNUMPOS = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    BigInt bigZERO = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    BigInt minusThirteen = {0xF3, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    BigInt res;

    big_val(res, 0xFFFFFFFFFFFFFEFF);
    assertBigInt(bigNUMNEG, res);

    big_val(res, 0x07FFFFFFFFFFFFFF);
    assertBigInt(bigNUMPOS, res);

    big_val(res, 0x0000000000000000);
    assertBigInt(bigZERO, res);

    big_val(res, 13);
    big_comp2(res, res);
    assertBigInt(minusThirteen, res);

    return 0;
}
