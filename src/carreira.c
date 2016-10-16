#include "carreira.h"

#include <stdio.h>
#include <stdlib.h>

// -- Faz a codificacao por carreira --
//
// Entrada: (1) vetor resultante
//			(2) vetor
//			(3) tamanho do vetor
// Saida: tamanho do resultado

int carreira_encoder(short ** result, short * buffer, int size){

	int i, j;
	int bit, counter0 = 0, counter1 = 0, auxAlt = 0, sizeResult = 0;

	short *aux = (short*) calloc (size*8, sizeof(short));

	for(i = 0; i<size; i++){

		for(j = 15; j >= 0; j--){

			bit = ((buffer[i] >> j) & 1);

			// Analisando os "0"s
			if(auxAlt == 0){

				if(bit == 0){

					counter0++;
					if((i == (size-1)) && (j == 0)){
						aux[sizeResult] = counter0;
						sizeResult++;
					}
					
				}
				else{

					aux[sizeResult] = counter0;
					auxAlt = 1;
					counter0 = 0;
					sizeResult++;
				}
			}

			// Analisando os "1"s
			if(auxAlt == 1){

				if(bit == 1){

					counter1++;
					if((i == (size-1)) && (j == 0)){
						aux[sizeResult] = counter1;
						sizeResult++;
					}
					
				}
				else{

					aux[sizeResult] = counter1;
					auxAlt = 0;
					counter0++;
					counter1 = 0;
					sizeResult++;

					if((i == (size-1)) && (j == 0)){
						aux[sizeResult] = counter0;
						sizeResult++;
					}
				}
			}	

		}	
	}

	*result = (short*) calloc(sizeResult, sizeof(short));

	for(i = 0; i<sizeResult; i++){
		*(*result + i) = aux[i];
	} 

	free(aux);

	return sizeResult;

}

// -- Faz a decodificacao por carreira --
//
// Entrada: (1) vetor resultante
//			(2) vetor
//			(3) tamanho do vetor
// Saida: tamanho do resultado

int carreira_decoder(short ** result, short * buffer, int size){

	int sizeResult = 0, auxCount = 15;
	int i, j;

	short *aux = (short*) calloc (size, sizeof(short));	

	// Como foi alocado com calloc, nao precisa armazenar os "0"s, somente os "1"s
	for(i = 0; i<size; i++){

		// Pulando os "0"s e armazenando os "1"s
		for(j = buffer[i]; j > 0; j--){

			// Elementos impares sao as quantidades de "1"s
			if((i % 2) != 0)
				aux[sizeResult] = aux[sizeResult] | (1 << auxCount);

			auxCount--;

			if(auxCount < 0){
				sizeResult++;
				auxCount = 15;
		 	}
		}
	}

	*result = (short*) calloc(sizeResult, sizeof(short));

	for(i = 0; i<sizeResult; i++){
		*(*result + i) = aux[i];
	} 

	free(aux);

	return sizeResult;
}