#include "bit_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// -- Valor maximo de um vetor --
//
// Entrada: (1) vetor 
//			(2) tamanho do vetor
// Saida: valor maximo do vetor

short valor_maximo(short * vet, int size){

	int i;
	short maior = 0;

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

short * merge_bits(short * vet, int size){

	int i, j;
	int min_bit, n_current, current, numero_zeros;
	long long merge;
	short * result;

	// Calcula o valor minimo de bits que pode ser usado para
	//representar o maior elemento do vetor
	int valormaximo = valor_maximo(vet, size);
	min_bit = log_2((double)valormaximo);

	// Alocando o vetor de saida
	double result_size = ceil(size*min_bit/16.0) + 1.0;
	result = (short*) malloc (sizeof(short)*result_size);

	// Valores iniciais da iteracao
	current = vet[0] << (16 - min_bit);
	n_current = min_bit;

	// De dois em dois elementos, transforma ambos em 32 bits,
	//faz a operacao de OR entre ambos e salva no vetor de resposta
	for (i = 1, j = 1; i < size; i++){

		merge = (current << 16) |  (vet[i] << (32 - min_bit - n_current));

		// Verifica se ainda eh possivel utilizar o byte ou se deve ir ao proximo
		if ((min_bit + n_current) < 16){
			current = (merge & 0xffff0000) >> 16;
			n_current += min_bit;
		}else{
			current = (merge & 0xffff);
			n_current += min_bit - 16;
			result[j] = (merge & 0xffff0000) >> 16;
			j++;
		}

		// Utilizado para o ultimo elemento
		if(i == size-1){
			result[j] = current;
			numero_zeros = 16 - n_current;
		}

	}

	// Header: numero minimo de bits necessario pra representar um elemento 
	//+ numero de zeros no finaldo arquivo + 00000000
	result[0] = ((min_bit & 0xf) << 12) | ((numero_zeros & 0xf) << 8);

	return result;
}

/*short * extend_bits(short * vet, int size){

	int i, j;
	int result_size, min_bit, numero_zeros, current;
	short * result;
	long long merge;

	min_bit = (vet[0] & 0xf0000000) >> 12;
	numero_zeros = (vet[0] & 0x0f000000) >> 8;

	result_size = (int)(ceil(((double)size-1.0)*16.0/min_bit));
	result = (short*) malloc (sizeof(short)*result_size);

	current = vet[0]; 

	for(i = 0, j = 1; i<result_size; i++){

		merge = (current << 16) |  vet[j];

		result[i] = merge &
	}

	return result;
}*/


