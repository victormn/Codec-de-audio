#include "diferenca.h"
#include "bit_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Faz a diferenca 2 a 2 entre os elementos de um vetor
short * diferenca_encoder(short * buffer, int size){

	int i;

	short *result = (short*) calloc (size, sizeof(short));

	result[0] = buffer[0];

	for (i=1; i<size; i++){

		result[i] = buffer[i-1] - buffer[i];

	}

	return result;
}

// Desfaz a diferenca 2 a 2 entre os elementos de um vetor
short * diferenca_decoder(short * buffer, int size){

	int i;

	short *result = (short*) calloc (size, sizeof(short));

	result[0] = buffer[0];

	for (i=1; i<size; i++){

		result[i] = result[i-1] - buffer[i];
	}

	return result;
}