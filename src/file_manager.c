#include "file_manager.h"

#include <stdio.h>
#include <stdlib.h>

// -- Leitura de um arquivo WAVE --
//
// Entrada: (1) nome do arquivo a ser lido 
//			(2) buffer para armazena-lo
// Saida: tamanho (bytes) do arquivo lido

int read_wave(char const *arg, char **buffer) {

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
	*buffer = (char*) malloc (sizeof(char)*fileSize);
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

int write_bin(char const *arg, char *buffer, int size){

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
