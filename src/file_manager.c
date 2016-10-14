#include "file_manager.h"

#include <stdio.h>
#include <stdlib.h>

// -- Leitura de um arquivo WAVE --
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
	result = fread (*buffer, 1, fileSize, f);
	if (result != fileSize) {
		printf("! Erro !\n\nBuffer nao recebeu o arquivo corretamente\n");
	    return EXIT_FAILURE;
	}

    fclose(f);

    return fileSize;
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

    fwrite (buffer , sizeof(char), size, f);
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

	*header = (short*) malloc(sizeof(short)*headerSize);
	*data = (short*) malloc(sizeof(short)*dataSize);

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
