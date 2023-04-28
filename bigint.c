/*Gabriel Zagury 2210912 3WB*/
/*Luiza Marcondes 2210275 3WA*/

#include "bigint.h"
#include <math.h>

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

/********** Operacoes aritmeticas ***********/

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
void big_sum(BigInt res, BigInt a, BigInt b)
{
    unsigned char overflow = 0; // se torna 1 se a soma de dois bytes for maior que 255 (0xFF)

    // para cada byte
    for (int i = 0; i < sizeof(BigInt); i++)
    {
        unsigned int tmp = a[i] + b[i] + overflow; // soma os dois bytes e o overflow da soma anterior (resto)
        overflow = (tmp > 0xff) ? 1 : 0;           // se a soma for maior que 255, overflow = 1
        res[i] = (unsigned char)tmp;               // guarda o byte menos significativo da soma
    }
}

/* res = a - b */
void big_sub(BigInt res, BigInt a, BigInt b)
{
    BigInt b_comp2;           // complemento de 2 de b
    big_comp2(b_comp2, b);    // b_comp2 = -b
    big_sum(res, a, b_comp2); // res = a + (-b)
}

/* res = a * b */
void big_mul(BigInt res, BigInt a, BigInt b);

/* Operacoes de deslocamento */

/* res = a << n */
void big_shl (BigInt res, BigInt a, int n){
  int j = 0;
  unsigned char c1, c2 = 0;
  
  for(int i = 0; i != sizeof(BigInt); i++)
    res[i] = a[i]; // passa a para res

  for(; j < n/8; j++){ // n/8 representa o numero de shifts de 8 bits a serem feitos
    for(int k = 15; k>-1; k--){ // caminha do final ao início
      if (k == 0)
        res[k] = 0; // preenche os iniciais com 0
      else
        res[k] = res[k-1]; // faz o shift de 8 bits para esquerda
    }
  }
  
  n = n%8; // pega o número de bits que precisa fazer o shift depois que os de bytes já terminaram 
  if(n){
    for(; j < 16; j++){ // aproveita o j para não precisar mexer os bytes já zerados
      c1 = res[j] / pow(2, (8 - n)); // guarda o que precisará passar para o próximo, já deslocado para direita a quantidade necessária para encaixar
      res[j] = (res[j] << n) | c2; // desloca para esquerda e acrescenta o que ele recebeu do anterior
      c2 = c1;
    }
  }

}

/* res = a >> n (logico) */
// unsigned shift
void big_shr(BigInt res, BigInt a, int n){
    int j = 0;
    unsigned char c1, c2 = 0; // c2 inicializado com 0 por ser unsigned shift
    
    for(int i = 0; i != sizeof(BigInt); i++)
        res[i] = a[i]; // passa a para res
    
    for(; j < n/8; j++){ // n/8 representa o numero de shifts de 8 bits a serem feitos
        for(int k = 0; (k + 1) < sizeof(BigInt); k++){ // caminha do início ao final
            if ((k + 1) == 15)
                res[k + 1] = 0; // preenche os finais com 0
            else
                res[k] = res[k + 1]; // faz o shift de 8 bits para direita
        }
    }
    
    n = n%8; // pega o número de bits que precisa fazer o shift depois que os de bytes já terminaram 
    j = sizeof(BigInt) - j; // começa da diferença para não precisar mexer nos bytes já zerados do final
    
    if(n){
        for(; j > -1; j--){ 
            // guarda o que precisará passar para o anterior na próxima iteração, já deslocado para esquerda a quantidade necessária para encaixar
            c1 = res[j] * pow(2, (8 - n)); 
            // desloca para direita e acrescenta o que ele recebeu da iteração anterior
            res[j] = (res[j] >> n) | c2; 
            c2 = c1;
        }
    }

}

/* res = a >> n (aritmetico) */
// signed shift
void big_sar(BigInt res, BigInt a, int n);
