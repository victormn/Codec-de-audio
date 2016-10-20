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
	int maior = 0;

	for(i=0; i<size; i++){

		if(abs(vet[i]) > maior)
			maior = abs(vet[i]);

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

	return result_int+1;
}

// -- Cria uma mascara para pegar os N ultimos bits (N = entrada) --
//
// Entrada: (1) N
// Saida: mascara

int mask(int n){
	return (int)(pow(2.0, (double)n)) - 1;
}

// -- Transforma um complemento 2 em um numero com um bit de sinal --
//
// Entrada: (1) numero
//			(2) numero minimo de bits para representar o sistema
// Saida: numero com um bit de sinal

short comp2_to_bit1(short a, int min_bit){

	if(a < 0) return abs(a) | (mask(min_bit-1)+1);
	else return a;

}

// -- Transforma um numero com um bit de sinal em um complemento 2 --
//
// Entrada: (1) numero
//			(2) numero minimo de bits para representar o sistema
// Saida: numero em complemento 2

short bit1_to_comp2(short a, int min_bit){

	if (a >> (min_bit-1) == 1) return (-1)*(a & mask(min_bit-1));
	else return a;

}

// -- Calcula o valor minimo de bits que pode ser usado para representar o maior elemento do vetor-
//
// Entrada: (1) vetor
//			(2) tamanho do vetor
// Saida: tamanho comprimido

int min_bit_calc(short *v, int size){
	return log_2((double)valor_maximo(v, size));
}

// -- Merge de elementos de um vetor com base no numero minimo para representa-los --
//
// Entrada: (1) vetor resultante
//			(2) vetor
//			(3) tamanho do vetor
// Saida: tamanho do vetor resultante

int merge_bits(short ** result, short * vet, int size){

	int i, j;
	int min_bit, n_current, current, numero_zeros;
	long long merge;

	min_bit = min_bit_calc(vet, size);

	// Alocando o vetor de saida
	double result_size = ceil(size*min_bit/16.0) + 1.0;
	*result = (short*) malloc (sizeof(short)*result_size);

	// Header: numero minimo de bits necessario pra representar um elemento 
	*(*result) = min_bit;

	// Se o vaor minimo de bits que pode ser usado para
	//representar = 16, nao ha o que comprimir
	if (min_bit == 16) {
		
		for (i = 0; i < size; i++)
			*(*result+i+1) = vet[i];

	}else{

		// Valores iniciais da iteracao
		current = comp2_to_bit1(vet[0],min_bit) << (16 - min_bit);
		n_current = min_bit;

		// De dois em dois elementos, transforma ambos em 32 bits,
		//faz a operacao de OR entre ambos e salva no vetor de resposta
		for (i = 1, j = 1; i < size; i++){

			merge = (current << 16) |  (comp2_to_bit1(vet[i],min_bit) << (32 - min_bit - n_current));

			// Verifica se ainda eh possivel utilizar o byte ou se deve ir ao proximo
			if ((min_bit + n_current) < 16){
				current = (merge & 0xffff0000) >> 16;
				n_current += min_bit;
			}else{
				current = (merge & 0xffff);
				n_current += min_bit - 16;
				*(*result+j) = (merge & 0xffff0000) >> 16;
				j++;
			}

			// Utilizado para o ultimo elemento
			if(i == size-1) *(*result+j) = current;
			
		}
	}


	return result_size;
}

// -- Extensão dos elementos de um vetor com base no numero minimo para representa-los --
//
// Entrada: (1) vetor resultante
//			(2) vetor
//			(3) tamanho do vetor
// Saida: tamanho do vetor resultante

int extend_bits(short ** result, short * vet, int size){

	int i, j;
	int result_size, n_current, min_bit;
	short aux;
	long long merge, current;

	// Obtendo o numero minimo de bits que o maior elemento pode ser representado
	min_bit = vet[0];

	// Obtendo o tamanho do vetor original e alocando ele
	result_size = (int)(floor(((double)size-1.0)*16.0/min_bit));
	*result = (short*) calloc (result_size+1, sizeof(short));

	if(min_bit == 16) {

		for(i = 0; i < result_size; i++)
			*(*result+i) = vet[i+1];

	}else{

		// Atribuindo valores iniciais
		aux = (vet[1] >> (16 - min_bit)) & mask(min_bit);
		*(*result) = bit1_to_comp2(aux, min_bit);
		current = vet[1] << 16 + min_bit;
		n_current = 16 - min_bit;

		// Obtendo os valores em 16 bits
		for(i = 1, j = 2; i < result_size; i++, j++){

			merge = (current) |  ((vet[j] << (16 - n_current)) & mask(32 - n_current));
			aux = (merge >> (32 - min_bit)) & mask(min_bit);
			*(*result+i) = bit1_to_comp2(aux, min_bit);
			current = merge << min_bit;
			n_current += 16 - min_bit;

			while(n_current >= 16){
				i++;
				aux = (current >> (32 - min_bit)) & mask(min_bit);
				*(*result+i) = bit1_to_comp2(aux, min_bit);
				current = current << min_bit;
				n_current -= min_bit;
			}

		}
	}

	return result_size;
}

int short2char(short * entrada, char ** saida, int size){

	int i;

	*saida = (char*) calloc (size*2, sizeof(char));

	for(i=0; i<size; i++){

		*(*saida+i+i) = (entrada >> 8) & 0xff;
		*(*saida+i+i+1) = (entrada) & 0xff;

	}

	return size*2;

}

