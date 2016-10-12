#include "bit_manager.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "testes.h"

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

// -- Cria uma mascara para pegar os N ultimos bits (N = entrada) --
//
// Entrada: (1) N
// Saida: mascara

int mask(int n){
	return (int)(pow(2.0, (double)n)) - 1;
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
		if(i == size-1) result[j] = current;
		
	}

	// Header: numero minimo de bits necessario pra representar um elemento 
	//+ numero de zeros no finaldo arquivo + 00000000
	result[0] = ((min_bit & 0xf) << 12);

	return result;
}



// -- Extensão dos elementos de um vetor com base no numero minimo para representa-los --
//
// Entrada: (1) vetor
//			(2) tamanho do vetor
// Saida: vetor com os novos elementos

short * extend_bits(short * vet, int size){

	int i, j;
	int result_size, n_current, min_bit;
	short * result;
	long long merge, current;

	// Obtendo o numero minimo de bits que o maior elemento pode ser representado
	// Obtendo a quantidade de zeros do final do arquivo
	min_bit = (vet[0] & 0xf000) >> 12;

	// Obtendo o tamanho do vetor original e alocando ele
	result_size = (int)(floor(((double)size-1.0)*16.0/min_bit));
	result = (short*) malloc (sizeof(short)*result_size);

	// Atribuindo valores iniciais
	result[0] = (vet[1] >> (16 - min_bit)) & mask(min_bit);
	current = vet[1] << 16 + min_bit;
	n_current = 16 - min_bit;

	// Obtendo os valores em 16 bits
	for(i = 1, j = 2; i < result_size; i++, j++){

		merge = (current) |  ((vet[j] << (16 - n_current)) & mask(32 - n_current));
		result[i] = (merge >> (32 - min_bit)) & mask(min_bit);
		current = merge << min_bit;
		n_current += 16 - min_bit;

		if(n_current >= 16){
			i++;
			result[i] = (current >> (32 - min_bit)) & mask(min_bit);
			current = current << min_bit;
			n_current -= min_bit;
		}

	}

	return result;
}

