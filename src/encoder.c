// 
//  Trabalho 1 - Codec de Audio
//
//  Alunos:
//      Elisa Jorge Marcatto        nUSP 7961965
//      Victor Marcelino Nunes      nUSP 8622381
//

#include "file_manager.h"
/*#include "carreira_codec.h"
#include "diferenca_codec.h"
#include "huffman_codec.h"*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
	
	FILE *output;
	int fileSize = 0;
    char *buffer;

	// Flags para saber quais metodos de codificacao serao utilizados
	int flag_diferenca = 0, flag_carreira = 0, flag_huffman = 0;

	// Verificando parametros de entrada
	if(argc < 3 || argc > 6){
		printf("! Erro ! Numero de argumentos errado !\n\nUtilize: ./encoder -d -c -h <entrada.wav> <saida.bin>\n");
		printf("As flags -d -c -h sao opcionais e podem ser inseridas em qualquer ordem\n");
		return EXIT_FAILURE;
	}

	// Verificando quais metodos de codificacao serao utilizados
	// obs: como o numero minimo de argumentos estabelecido foi 3, deve-se verificar se ha mais que 3 argumentos
	//antes de verificar o argv[3]
	if(strcmp (argv[1], "-d") == 0 || strcmp (argv[2], "-d") == 0 || (argc > 3 && strcmp (argv[3], "-d") == 0))
		flag_diferenca = 1;

	if(strcmp (argv[1], "-c") == 0 || strcmp (argv[2], "-c") == 0 || (argc > 3 && strcmp (argv[3], "-c") == 0))
		flag_carreira = 1;

	if(strcmp (argv[1], "-h") == 0 || strcmp (argv[2], "-h") == 0 || (argc > 3 && strcmp (argv[3], "-h") == 0))
		flag_huffman = 1;

	// Verificando entradas invalidas (serao ignoradas)
	if(argc >= 4 && strcmp (argv[1], "-d") != 0 && strcmp (argv[1], "-c") != 0 && strcmp (argv[1], "-h") != 0)
		printf("Argumento '%s' ignorado\n", argv[1]);

	if(argc >= 5 && strcmp (argv[2], "-d") != 0 && strcmp (argv[2], "-c") != 0 && strcmp (argv[2], "-h") != 0)
		printf("Argumento '%s' ignorado\n", argv[2]);

	if(argc == 6 && strcmp (argv[3], "-d") != 0 && strcmp (argv[3], "-c") != 0 && strcmp (argv[3], "-h") != 0)
		printf("Argumento '%s' ignorado\n", argv[3]);


	// Lendo o arquivo WAVE (penultimo parametro)
	fileSize = read_wave(argv[argc-2], &buffer);

/*	// Codificacao por CARREIRA
	if(flag_carreira == 1)
		fileSize = carreira_encoder(&buffer, fileSize);

	// Codificacao por DIFERENCA
	if(flag_diferenca == 1)
		fileSize = diferenca_encoder(&buffer, fileSize);

	// Codificacao por HUFFMAN
	if(flag_huffman == 1)
		fileSize = huffman_encoder(&buffer, fileSize);*/

	// Escrevendo a stream de dados no arquivo passado como ultimo parametro
	write_bin(argv[argc-1], buffer, fileSize);

	return 0;
}
