#include "testes.h"
#include "bit_manager.h"

#include <stdio.h>
#include <math.h>

// -- Acessar bit a bit de um dado numero --
//
// Entrada: (1) numero

void contador_bit_a_bit(int n, int size){

    int i;

    for(i = size-1; i >= 0; i--)
        printf("%d", (n >> i) & 0x01);

    printf("\n");

}

// -- Imprime dois vetores lado a lado --
//
// Entrada: (1) vetor 1
//			(2) vetor 2
//			(3) tamanho dos vetores

void print_vetores (short * vet1, short * vet2, int size){

	for (int i = 0; i < size; ++i){

		printf("%d %d\n", vet1[i], vet2[i]);
	}
}

// -- Faz shift em um numero --
//
// Entrada: (1) numero
//			(2) quantidade a ser shifitada

void shift(int n, int s){

	long long int s2 = n << s;

	printf("%llu\n", s2);

	contador_bit_a_bit(s2, log_2((double)s2));

}