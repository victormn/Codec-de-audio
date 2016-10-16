#include "file_manager.h"

#include <stdio.h>
#include <stdlib.h>

// -- Leitura de um arquivo --
//
// Entrada: (1) nome do arquivo a ser lido 
//			(2) buffer para armazena-lo
// Saida: tamanho (bytes) do arquivo lido

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

// -- Escreve uma stream de dados em um arquivo de entrada --
//
// Entrada: (1) nome do arquivo que ira receber a stream de dados 
//			(2) stream a ser escrita
//			(3) tamanho da stream
// Saida: 0, se sucesso, mensagem de erro, se falhar

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

// -- Remove o header e salva ele numa variavel --
//
// Entrada: (1) vetor que ira receber o header 
//			(2) vetor que ira receber o restante dos dados 
//			(3) arquivo que sera separado
//			(4) tamanho do arquivo
//			(5) tamanho do header
// Saida: tamanho dos dados

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

// -- Junta o header com o restante dos arquivos --
//
// Entrada: (1) vetor que ira receber o arquivo 
//			(2) header 
//			(3) restante dos dados
//			(4) tamanho do arquivo
//			(5) tamanho do header
// Saida: tamanho do arquivo final

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

// -- Adiciona flags que indicam o tipo de codificacao utilizada --
//
// Entrada: (1) vetor resultante
//			(2) vetor
//			(3) tamanho do vetor
//			(4) flag da codificacao por diferenca
//			(5) flag da codificacao por carreira
//			(6) flag da codificacao por huffman
// Saida: tamanho do resultado

int merge_compress_flags(short **result, short *file, int size, int d, int c, int h){

	int i;

	*result = (short*) calloc((size+1), sizeof(short));

	*(*result) = (d << 2) | (c << 1) | h;

	for (i = 0; i<size; i++)
		*(*result+i+1) = file[i];

	return size+1;
}

// -- Remove flags que indicam o tipo de codificacao utilizada --
//
// Entrada: (1) vetor resultante
//			(2) vetor
//			(3) tamanho do vetor
// Saida: tamanho do resultado

int remove_compress_flags(short **result, short *file, int size){

	int i;

	*result = (short*) calloc((size-1), sizeof(short));

	for (i = 1; i<size; i++)
		*(*result+i-1) = file[i];

	return size-1;
}

// -- Divide o vetor em: primeira metade = primeiro canal; segunda metade = segundo canal --
//
// Entrada: (1) vetor 
//			(2) tamanho do vetor
// Saida: vetor resultante

short * split_channels(short *file, int size){

	int i, j;

	short * result = (short*) calloc(size, sizeof(short));

	for(i=0, j=0; i < (size/2); i++, j+=2)
		result[i] = file[j];
	

	for(i=(size/2), j=1; i < size; i++, j+=2)
		result[i] = file[j];

	return result;
}

// -- Junta os canais do vetor, colocandos-os alternadamente em seus elementos --
//
// Entrada: (1) vetor 
//			(2) tamanho do vetor
// Saida: vetor resultante

short * merge_channels(short *file, int size){

	int i, j;

	short * result = (short*) calloc(size, sizeof(short));

	for(i=0, j=0; i < (size/2); i++, j+=2)
		result[j] = file[i];
	

	for(i=(size/2), j=1; i < size; i++, j+=2)
		result[j] = file[i];

	return result;
}


