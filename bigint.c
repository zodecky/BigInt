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
    for (int i = 0; i < sizeof(BigInt); i++)
    {
        if (res[i] != 0xFF) // se tiver espaço para somar 1 (não for 1111 1111), não vai precisar levar o 1 para somar no próximo byte, então pode sair do for
        {
            res[i]++;
            break;
        }
        res[i]++;
    }
}

/* res = a + b */

void big_sum_luiza(BigInt res, BigInt a, BigInt b)
{
    int bitA = 0, bitB = 0, bitR = 0, overflow = 0;
    for (int i = 0; i < sizeof(BigInt); i++)
    {

        if (overflow && (a[i] != 0xFF))
        { // verifica se cabe o overflow de + 1 no a
            a[i] = a[i] + overflow;
            overflow = 0;
        }
        else if (overflow && (b[i] != 0xFF))
        { // verifica se cabe o overflow de + 1 no b
            b[i] = b[i] + overflow;
            overflow = 0;
        }
        // caso não entre nessas condições, a flag de overflow continua como 1 para passar à próxima iteração

        if ((a[i] & 0x80) == 0x80)
        { // guarda numa variável se o bit mais significativo de a é 1 ou 0
            bitA = 1;
        }
        else
            bitA = 0;

        if ((b[i] & 0x80) == 0x80)
        { // guarda numa variável se o bit mais significativo de b é 1 ou 0
            bitB = 1;
        }
        else
            bitB = 0;

        // (0x7F = 0111 1111)
        a[i] = a[i] & 0x7F; // zera o bit mais significativo de a para não dar overflow na conta
        b[i] = b[i] & 0x7F; // zera o bit mais significativo de b para não dar overflow na conta

        res[i] = a[i] + b[i]; // faz a soma

        if ((res[i] & 0x80) == 0x80)
        { // guarda numa variável se o bit mais significativo do resultado é 1 ou 0
            bitR = 1;
        }
        else
            bitR = 0;

        if (bitA + bitB == 2)
        { // se os dois antes de somar já tinham esse bit igual a 1, vai dar overflow
            overflow = 1;
        }
        else if ((bitA || bitB) && bitR)
        { // se um deles era 1 e na soma o resultado ficou com bit mais significativo 1 também, vai dar overflow
            overflow = 1;
            res[i] = res[i] & 0x7F; // zera o bit mais significativo do resultado, pois o 1 é passado no overflow
        }
    }
}

void big_sum(BigInt res, BigInt a, BigInt b)
{
    unsigned char overflow = 0; // se torna 1 se a soma de dois bytes for maior que 255 (0xFF)

    // para cada byte
    for (int i = 0; i < sizeof(BigInt); i++)
    {
        unsigned int tmp = a[i] + b[i] + overflow; // soma os dois bytes e o overflow da soma anterior (resto)
        overflow = (tmp > 0xff) ? 1 : 0;           // se a soma for maior que 255, overflow = 1
        res[i] = tmp & 0xff;
    }
}

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
