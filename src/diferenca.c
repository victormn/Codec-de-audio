#include "diferenca.h"
#include "bit_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// -- Faz a diferenca 2 a 2 entre os elementos de um vetor --
//
// Entrada: (1) vetor
//			(2) tamanho do vetor
// Saida: vetor com as diferencas 2 a 2

short * diferenca_encoder(short * buffer, int size){

	int i;

	short *result = (short*) calloc (size, sizeof(short));

	result[0] = buffer[0];

	for (i=1; i<size; i++){

		result[i] = buffer[i-1] - buffer[i];

	}

	return result;
}

// -- Desfaz a diferenca 2 a 2 entre os elementos de um vetor --
//
// Entrada: (1) vetor
//			(2) tamanho do vetor
// Saida: vetor com os elementos originais

short * diferenca_decoder(short * buffer, int size){

	int i;

	short *result = (short*) calloc (size, sizeof(short));

	result[0] = buffer[0];

	for (i=1; i<size; i++){

		result[i] = result[i-1] - buffer[i];
	}

	return result;
}