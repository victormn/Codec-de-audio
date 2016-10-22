#include "file_manager.h"
#include "bit_manager.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Leitura de um arquivo
int read_wave(char const *arg, short **buffer) {

    FILE *f;    
    int fileSize = 0;
    size_t result;

    // Verificando se foi possivel abrir o arquivo
    f = fopen(arg, "rb");
    if(f == NULL) {
	    printf("! Erro !\n\nNao foi possivel abrir o arquivo '%s'\n", arg);
	    return EXIT_FAILURE;
    }

    // Obtendo o tamanho do arquivo
	fseek (f , 0 , SEEK_END);
	fileSize = ftell (f);
	rewind (f);

    // Alocando um buffer para armazenar os dados do arquivo
	*buffer = (short*) calloc(fileSize, sizeof(short));
	if (*buffer == NULL) {
	    printf("! Erro !\n\nMemoria nao alocada para o buffer\n");
	    return EXIT_FAILURE;
	}

    // Lendo o arquivo
	result = fread (*buffer, 2, fileSize, f);
	if (result != fileSize/2) {
		printf("! Erro !\n\nBuffer nao recebeu o arquivo corretamente\n");
	    return EXIT_FAILURE;
	}

    fclose(f);

    return result;
}

// Escreve uma stream de dados em um arquivo de entrada
int write_bin(char const *arg, short *buffer, int size){

 	FILE *f;

    // Verificando se foi possivel abrir o arquivo
    f = fopen(arg, "wb");
    if(f == NULL) {
	    printf("! Erro !\n\nNao foi possivel abrir o arquivo '%s'\n", arg);
	    return EXIT_FAILURE;
    }

    fwrite (buffer , 2, size, f);
  	fclose (f);

  	return 0;

 }

// Remove o header e salva ele numa variavel
int split_header(short **header, short **data, short * file, int fileSize, int headerSize){

	int i, j;
	int dataSize = fileSize - headerSize;

	*header = (short*) calloc(headerSize, sizeof(short));
	*data = (short*) calloc(dataSize+1, sizeof(short));

	for(i = 0; i<headerSize; i++)
		*(*header+i) = file[i];	

	for(i = headerSize, j = 0; i<fileSize; i++, j++)
		*(*data+j) = file[i];

	return dataSize;
}

// Junta o header com o restante dos arquivos
int merge_header(short **file, short *header, short * data, int dataSize, int headerSize){

	int i, j;
	int fileSize = dataSize + headerSize;

	*file = (short*) malloc(sizeof(short)*fileSize);

	for(i = 0; i<headerSize; i++)
		*(*file+i) = header[i];	

	for(i = headerSize, j = 0; i<fileSize; i++, j++)
		*(*file+i) = data[j];

	return fileSize;
}

// Adiciona flags que indicam o tipo de codificacao utilizada
int merge_compress_flags(short **result, short *file, int size, int d, int c, int h){

	int i;

	*result = (short*) calloc((size+1), sizeof(short));

	*(*result) = (d << 2) | (c << 1) | h;

	for (i = 0; i<size; i++)
		*(*result+i+1) = file[i];

	return size+1;
}

// Remove flags que indicam o tipo de codificacao utilizada
int remove_compress_flags(short **result, short *file, int size){

	int i;

	*result = (short*) calloc((size-1), sizeof(short));

	for (i = 1; i<size; i++)
		*(*result+i-1) = file[i];

	return size-1;
}

// Divide o vetor em: primeira metade = primeiro canal; segunda metade = segundo canal
short * split_channels(short *file, int size){

	int i, j;

	short * result = (short*) calloc(size, sizeof(short));

	for(i=0, j=0; i < (size/2); i++, j+=2)
		result[i] = file[j];
	

	for(i=(size/2), j=1; i < size; i++, j+=2)
		result[i] = file[j];

	return result;
}

// Junta os canais do vetor, colocandos-os alternadamente em seus elementos
short * merge_channels(short *file, int size){

	int i, j;

	short * result = (short*) calloc(size, sizeof(short));

	for(i=0, j=0; i < (size/2); i++, j+=2)
		result[j] = file[i];
	

	for(i=(size/2), j=1; i < size; i++, j+=2)
		result[j] = file[i];

	return result;
}

// Seapara um vetor que possui 16 bits por elementos em um vetor
//com o dobro do tamanho onde cada elemento esta limitado por 8 bits
int split_in_8bits(short ** result, short *file, int size){

	int i, n;

	n = 2;

	*result = (short*) calloc (size*n, sizeof(short));

	for(i=0; i<size; i++){

		*(*result+(i*n)) = (file[i] >> 8) & 0xff;
		*(*result+(i*n) + 1) = (file[i]) & 0xff;
	}

	return size*n;
}

// Trasforma um vetor que possui 8 bits por elementos em um vetor
//com a metade do tamanho onde cada elemento passara a possuir 16 bits
int merge_in_16bits(short ** result, short *file, int size){

	int i, newsize, n;

	n = 2;

	*result = (short*) calloc (size/n, sizeof(short));

	newsize = size/n;

	for(i=0; i<newsize; i++){

		*(*result+i) = ((file[i*n] << 8) & 0xff00) | ((file[i*n+1]) & 0xff);

	}

	return newsize;
}


// Merge de elementos de um vetor com base no numero minimo para representa-los
int merge_bits(short ** result, short * vet, int size){

	int i, j;
	int min_bit, n_current, current;
	long long merge;

	// Numero minimo para representar o valor maximo
	min_bit = min_bit_calc(vet, size);

	// Alocando o vetor de saida
	double result_size = ceil(size*min_bit/16.0) + 1.0;
	*result = (short*) malloc (sizeof(short)*result_size);

	// Header: numero minimo de bits necessario pra representar um elemento 
	*(*result) = min_bit;

	// Se o vaor minimo de bits que pode ser usado para
	//representar > 15, nao ha o que comprimir
	if (min_bit > 15) {
		
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

// Extensão dos elementos de um vetor com base no numero minimo para representa-los (processo inverso do merge)
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

	if(min_bit > 15) {

		for(i = 0; i < result_size; i++)
			*(*result+i) = vet[i+1];

	}else{

		// Atribuindo valores iniciais
		aux = (vet[1] >> (16 - min_bit)) & mask(min_bit);
		*(*result) = bit1_to_comp2(aux, min_bit);
		current = vet[1] << (16 + min_bit);
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