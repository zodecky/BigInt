/*Gabriel Zagury 2210912 3WB*/
/*Luiza Marcondes 2210275 3WA*/

#include "bigint.h"

void big_val(BigInt res, long val)
{
    int i = 0;
    for (; i < 8; i++)
    {
        res[i] = (val & 0x00000000000000FF); // seleciona apenas o byte menos significativo para colocar no vetor
        val = val >> 8;                      // desloca para pegar o próximo byte menos significativo
    }

    /*
    res[7] é o BYTE mais significativo.
    0x80 = 1000 0000 (testar se o BIT mais significativo é 1)
    */
    if ((res[7] & 0x80) == 0x80) // se é negativo (o bit mais significativo é 1)
    {
        for (; i < sizeof(BigInt); i++)
        {
            res[i] = 0xFF; // extende com 1 (sinal negativo)
        }
    }
    else
    {
        for (; i < sizeof(BigInt); i++) // se é positivo (o bit mais significativo é 0)
        {
            res[i] = 0x00; // extende com 0 (sinal positivo)
        }
    }
}

/* Operacoes aritmeticas */

/* res = -a */
void big_comp2(BigInt res, BigInt a)
{
    for (int i = 0; i < sizeof(BigInt); i++)
    {
        res[i] = ~a[i]; // inverte todos os bits
    }
    res[0]++; // soma 1 no byte menos significativo
}

/* res = a + b */
void big_sum(BigInt res, BigInt a, BigInt b);

/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b);

/* res = a * b */
void big_mul(BigInt res, BigInt a, BigInt b);

/* Operacoes de deslocamento */

/* res = a << n */
void big_shl(BigInt res, BigInt a, int n);

/* res = a >> n (logico) */
void big_shr(BigInt res, BigInt a, int n);

/* res = a >> n (aritmetico) */
void big_sar(BigInt res, BigInt a, int n);
