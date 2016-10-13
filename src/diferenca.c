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

int diferenca_encoder(short ** result, short * buffer, int size){

	int i, resultSize = 0;
	short DCValue;

	short *aux = (short*) malloc (sizeof(short)*size);

	DCValue = buffer[0];

	aux[0] = DCValue - buffer[1];

	for (i=1; i<size; i++){

		aux[i-1] = buffer[i-1] - buffer[i];

	}

	int min_bit = size_of_result(aux, size);

	resultSize = ceil(size*min_bit/16.0) + 1.0;

	*result = (short*) malloc (sizeof(short)*resultSize);
	*result = merge_bits(aux, size-1, DCValue);

	free(aux);

	return resultSize;
}

// -- Faz a diferenca 2 a 2 entre os elementos de um vetor --
//
// Entrada: (1) vetor
//			(2) tamanho do vetor
// Saida: vetor com as diferencas 2 a 2

int diferenca_decoder(short ** result, short * buffer, int size){

	int i, resultSize = 0;
	short DCValue;

	int min_bit = buffer[0];
	min_bit++;
	resultSize = (int)(floor(((double)size-2.0)*16.0/min_bit));
	resultSize++;

	short *aux = (short*) malloc (sizeof(short)*resultSize);
	aux = extend_bits(buffer, size, &DCValue);

	*result = (short*) malloc (sizeof(short)*resultSize);

	*(*result) = DCValue;

	for (i=1; i<resultSize; i++){
		*(*result+i) = *(*result+(i-1)) - aux[i-1];
	}

	free(aux);

	return resultSize;
}