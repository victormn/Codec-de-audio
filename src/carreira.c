#include "carreira.h"

#include <stdio.h>
#include <stdlib.h>



int carreira_encoder(short ** result, short * buffer, int size){

	int zeroCount, oneCount, lastCount = 0, initCount = 0;
	int i, j, k;

	short *aux = (short*) calloc (size*8, sizeof(short));

	k = 0;

	for(i = 0; i<size; i++){

		// Analisa cada bit de um elemento do vetor
		for(j = 15; ;){

			zeroCount = 0;
			oneCount = 0;

			while(((buffer[i] >> j) & 0x1) == 0){

				if((j == 15) && (initCount == 0))
					zeroCount += lastCount;
				else zeroCount++;
				j--;

				if (j < 0){

					if (i == (size-1)){
						aux[k] = zeroCount;
					}else{
						initCount = 0;
						lastCount = zeroCount;
					}
					break;
				}

			}
			while(((buffer[i] >> j) & 0x1) == 1){

				if((j == 15) && (initCount == 1))
					oneCount += lastCount;
				else oneCount++;
				j--;

				if (j < 0){

					if (i == (size-1)){
						aux[k] = oneCount;
					}else{
						initCount = 1;
						lastCount = oneCount;
					}
					break;
				}
			}

			if(j<0) break;

			if(!((j == 15) && (initCount == 1))){
				aux[k] = zeroCount;
				k++;
			}
			
			if(!((j == 15) && (initCount == 0))){
				aux[k] = oneCount;
				k++;
			}
     
		}
	}

	*result = (short*) calloc(k, sizeof(short));

	for(i = 0; i<k; i++){
		*(*result + i) = aux[i];
	} 

	free(aux);

	return k;
}

int carreira_decoder(short ** result, short * buffer, int size){

	int resultSize = 0, count = 0;


	return resultSize;
}