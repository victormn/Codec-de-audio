#include "bit_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Retorna o valor maximo do vetor "vet"
short valor_maximo(short * vet, int size){

	int i;
	int maior = 0;

	for(i=0; i<size; i++){

		if(abs(vet[i]) > maior){
			maior = abs(vet[i]);
		}

	}

	return maior;
}

// Retorna o log na base 2 da entrada "x"
int log_2(double x){

	if(x == 0) return 1;

	double result = ceil(log(x+1)/log(2));
	int result_int = result;

	return result_int+1;
}

// Calcula o valor minimo de bits que pode ser usado para representar o maior elemento do vetor
int min_bit_calc(short *v, int size){
	return log_2((double)abs(valor_maximo(v, size)));
}

// Cria uma mascara para pegar os N ultimos bits (N = entrada)
int mask(int n){
	return (int)(pow(2.0, (double)n)) - 1;
}

// Transforma um complemento 2 em um numero com um bit de sinal
short comp2_to_bit1(short a, int min_bit){

	if(a < 0) return abs(a) | (mask(min_bit-1)+1);
	else return a;

}

// Transforma um numero com um bit de sinal em um complemento 2
short bit1_to_comp2(short a, int min_bit){

	if (a >> (min_bit-1) == 1) return (-1)*(a & mask(min_bit-1));
	else return a;

}

