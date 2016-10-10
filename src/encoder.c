// 
//  Trabalho 1 - Codec de Audio
//
//  Alunos:
//      Elisa Jorge Marcatto        nUSP 7961965
//      Victor Marcelino Nunes      nUSP 8622381
//

#include "file_manager.h"
#include "bit_manager.h"
// #include "carreira.h"
#include "diferenca.h"
// #include "huffman.h"

#include "testes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
	
	FILE *output;
	int fileSize = 0;
    char *buffer;
    int i;

	// Flags para saber quais metodos de codificacao serao utilizados
	int flag_diferenca = 0, flag_carreira = 0, flag_huffman = 0;

	// Verificando parametros de entrada
	if(argc < 3 || argc > 6){
		printf("! Erro ! Numero de argumentos errado !\n\nUtilize: ./encoder -d -c -h <entrada.wav> <saida.bin>\n");
		printf("As flags -d -c -h sao opcionais e podem ser inseridas em qualquer ordem\n");
		return EXIT_FAILURE;
	}

	// Verificando quais metodos de codificacao serao utilizados
	for (i = 1; i < argc-2; i++){
		if(strcmp (argv[i], "-d") == 0) flag_diferenca = 1;
		else if(strcmp (argv[i], "-c") == 0) flag_carreira = 1;
		else if(strcmp (argv[i], "-h") == 0) flag_huffman = 1;
		else printf("Argumento '%s' ignorado\n", argv[i]);
	}

	// Lendo o arquivo WAVE (penultimo parametro)
	fileSize = read_wave(argv[argc-2], &buffer);

/*	// Codificacao por DIFERENCA
	if(flag_diferenca == 1)
		fileSize = diferenca_encoder(&buffer, fileSize);

	// Codificacao por CARREIRA
	if(flag_carreira == 1)
		fileSize = carreira_encoder(&buffer, fileSize);

	// Codificacao por HUFFMAN
	if(flag_huffman == 1)
		fileSize = huffman_encoder(&buffer, fileSize);*/

	// Escrevendo a stream de dados no arquivo passado como ultimo parametro
	write_bin(argv[argc-1], buffer, fileSize);

// ------------------------------- JUST FOR TEST -------------------------------------------

	int valormaximo = valor_maximo(buffer, fileSize);
	int logdovalormaximo = log_2((double)valormaximo);
	printf("%d %d\n", valormaximo, logdovalormaximo);

	char * dif = diferenca_byte_a_byte(buffer, fileSize);

	valormaximo = valor_maximo(dif, fileSize);
	logdovalormaximo = log_2((double)valormaximo);
	printf("%d %d\n", valormaximo, logdovalormaximo);

	//print_vetores(buffer, dif, fileSize);

printf("%d\n", log_2(89));

	return 0;
}