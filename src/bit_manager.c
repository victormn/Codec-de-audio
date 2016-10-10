#include "bit_manager.h"

#include <stdio.h>
#include <math.h>

// -- Valor maximo de um vetor --
//
// Entrada: (1) vetor 
//			(2) tamanho do vetor
// Saida: valor maximo do vetor

char valor_maximo(char * vet, int size){

	int i;
	char maior = 0;

	for(i=0; i<size; i++){

		if(vet[i] > maior)
			maior = vet[i];

	}

	return maior;
}

// -- Log na base 2 de um numero --
//
// Entrada: (1) numero 
// Saida: log na base 2 da entrada

int log_2(double x){

	if(x == 0) return 1;

	double result = ceil(log(x+1)/log(2));
	int result_int = result;

	return result_int;
}

// -- Merge de elementos de um vetor com base no numero minimo para representa-los --
//
// Entrada: (1) vetor
//			(2) tamanho do vetor
// Saida: tamanho (bytes) do arquivo lido

int merge_bits(char * vet, int size){


}



