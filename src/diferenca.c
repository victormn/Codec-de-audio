#include "diferenca.h"

#include <stdio.h>
#include <stdlib.h>

// -- Faz a diferenca 2 a 2 entre os elementos de um vetor --
//
// Entrada: (1) vetor
//			(2) tamanho do vetor
// Saida: vetor com as diferencas 2 a 2

char * diferenca_2_a_2(char * buffer, int size){

	int i;
	char *vet;

	vet = (char*) malloc (sizeof(char)*size);

	vet[0] = buffer[0];

	for (i=0; i<size; i++){

		vet[i+1] = buffer[i] - buffer[i+1];

	}

	return vet;
}