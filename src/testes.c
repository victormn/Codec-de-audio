#include "testes.h"

#include <stdio.h>
#include <math.h>

// -- Acessar bit a bit de um dado numero --
//
// Entrada: (1) numero

void contador_bit_a_bit(int n){

    int i;

    for(i = 7; i >= 0; i--)
        printf("%d", (n >> i) & 0x01);

    printf("\n");

}

// -- Imprime dois vetores lado a lado --
//
// Entrada: (1) vetor 1
//			(2) vetor 2
//			(3) tamanho dos vetores

void print_vetores (char * vet1, char * vet2, int size){

	for (int i = 0; i < size; ++i){

		printf("%d %d\n", vet1[i], vet2[i]);
	}
}