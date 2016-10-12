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

#include <math.h>

int main(int argc, char const *argv[]){
	
	int fileSize = 0;
    short *buffer;
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

	// Codificacao por DIFERENCA
	if(flag_diferenca == 1){
		//fileSize = diferenca_encoder(&buffer, fileSize);
	}

	// Codificacao por CARREIRA
	if(flag_carreira == 1){
		//fileSize = carreira_encoder(&buffer, fileSize);
	}

	// Codificacao por HUFFMAN
	if(flag_huffman == 1){
		//fileSize = huffman_encoder(&buffer, fileSize);
	}

	// Escrevendo a stream de dados no arquivo passado como ultimo parametro
	write_bin(argv[argc-1], buffer, fileSize);

// ------------------------------------------------------ JUST FOR TEST -----------------------------------------------------------

	
	// -------------------TESTEANDO A DIFERENCA 2 A 2 -----------------------------------------------------------------------------

/*	int valormaximo = valor_maximo(buffer, fileSize);
	int logdovalormaximo = log_2((double)valormaximo);

	char * dif = diferenca_2_a_2(buffer, fileSize);

	valormaximo = valor_maximo(dif, fileSize);
	logdovalormaximo = log_2((double)valormaximo);

	print_vetores(buffer, dif, fileSize);*/

	// --------------------TESTANDO CONTADOR BIT A BIT PARA NEGATIVO --------------------------------------------------------------

/*	contador_bit_a_bit(-1);

	printf("%d\n", 0b11111111);*/

	// --------------------TESTANDO SHIFT -----------------------------------------------------------------------------------------

/*	shift(31, 11);*/

	// -------------------TESTEANDO O MERGE_BITS-----------------------------------------------------------------------------------

	short teste[9] = {0b0001111111111111, 0b0000111111111111, 0b0000111111111111, 0b0000111111111111, 0b0000111111111111, 
		0b0000111111111111, 0b0000111111111111, 0b0000111111111111, 0b0000111111111111};


	short * result = merge_bits(teste, 9);

	for (i = 0; i < 9; ++i){
		
		contador_bit_a_bit(teste[i], 16);

	}

	printf("\n");

	for (i = 0; i < 9; ++i){
		
		contador_bit_a_bit(result[i], 16);

	}

	short * outroresult = extend_bits(result, 9);

	printf("\n");

	for (i = 0; i < 9; ++i){
		
		contador_bit_a_bit(outroresult[i], 16);

	}

	// ---------------------------------------------------------------------------------------------------------------------------
	
	return 0;
}


