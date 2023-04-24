/*Gabriel Zagury 2210912 3WB*/
/*Luiza Marcondes 2210275 3WA*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bigint.h"

#define assertBigInt(esperado, atual)                                                                                             \
    do                                                                                                                            \
    {                                                                                                                             \
        const unsigned char *esperado_arr = (esperado);                                                                           \
        const unsigned char *atual_arr = (atual);                                                                                 \
        long long esperado_num = 0, atual_num = 0;                                                                                \
        for (int i = 0; i < 8; i++)                                                                                               \
        {                                                                                                                         \
            esperado_num |= ((long long)esperado_arr[i] << (i * 8));                                                              \
            atual_num |= ((long long)atual_arr[i] << (i * 8));                                                                    \
        }                                                                                                                         \
        if (esperado_num != atual_num)                                                                                            \
        {                                                                                                                         \
            fprintf(stderr, "Assert falhou: esperado %lld, mas recebeu %lld\tNA LINHA: %d\n", esperado_num, atual_num, __LINE__); \
            exit(1);                                                                                                              \
        }                                                                                                                         \
    } while (0)

#define BIGINT_SIZE NUM_BITS / 8

#define assertBigIntHEX(esperado, atual)                   \
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
    BigInt res2;
    BigInt check;

    big_val(res, 0xFFFFFFFFFFFFFEFF);
    assertBigIntHEX(bigNUMNEG, res);

    big_val(res, 0x07FFFFFFFFFFFFFF);
    assertBigIntHEX(bigNUMPOS, res);

    big_val(res, 0x0000000000000000);
    assertBigIntHEX(bigZERO, res);

    big_val(res, 13);
    big_comp2(res, res);
    assertBigIntHEX(minusThirteen, res);

    big_val(res, 0x000000000000FFFA);
    big_val(check, 0x000000000001FFF4);
    big_sum(res, res, res);
    assertBigIntHEX(check, res);

    big_val(res, 1345689);
    big_val(res2, -17483920);
    big_val(check, -16138231);
    big_sum(res, res, res2);
    assertBigInt(check, res);

    big_val(res, 0x0000000000000000);
    big_val(res2, 0x0000000000000000);
    big_val(check, 0x0000000000000000);
    big_sum(res, res, res2);
    assertBigInt(check, res);

    big_val(res, 0xFFFFFFFFFFFFFFFF);
    big_val(res2, 0x0000000000000001);
    big_val(check, 0x0000000000000000);
    big_sum(res, res, res2);

    big_val(res, 0xFFFFFFFFFFFFFFFF); // -1
    big_val(check, -2);
    big_sum(res, res, res);
    assertBigInt(check, res);

    printf("Todos os testes passaram com sucesso!\n");

    return 0;
}
