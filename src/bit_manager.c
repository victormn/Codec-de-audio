#include "bit_manager.h"

#include <stdio.h>
#include <stdlib.h>
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
// Saida: vetor com os novos elementos

char * merge_bits(char * vet, int size){

	int i, j = 0;
	int min_bit, n_current, current;
	long merge;
	char * result;

	// Calcula o valor minimo de bits que pode ser usado para
	//representar o maior elemento do vetor
	int valormaximo = valor_maximo(vet, size);
	min_bit = log_2((double)valormaximo);

	// Alocando o vetor de saida
	int result_size = (int)ceil(size/8*min_bit);
	result = (char*) malloc (sizeof(char)*result_size);

	// Valores iniciais da iteracao
	current = vet[0] << (8 - min_bit);
	n_current = min_bit;

	// De dois em dois elementos, transforma ambos em 16 bits,
	//faz a operacao de OR entre ambos e salva no vetor de resposta
	for (i = 1; i < size; i++){

		merge = (current << 8) |  (vet[i] << (16 - min_bit - n_current));

		// Verifica se ainda eh possivel utilizar o byte ou se deve ir ao proximo
		if ((min_bit + n_current) < 8){
			current = (merge & 0xff00) >> 8;
			n_current += min_bit;
		}else{
			current = (merge & 0xff);
			n_current += min_bit - 8;
			result[j] = (merge & 0xff00) >> 8;
			j++;
		}

		// Utilizado para o ultimo elemento
		if(i == size-1)	result[j] = (merge & 0xff00) >> 8;	

	}

	return result;
}



