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
	
	int currentSize = 0;
    short *buffer, *currentData;
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
	currentSize = read_wave(argv[argc-2], &buffer);

	// Current data sempre ira receber os valores do vetor de short que sera trabalhado
	currentData = buffer;

	// Separando o header dos dados do audio
	short * header;
	short * data;

	currentSize = split_header(&header, &data, buffer, currentSize, 44);
	currentData = data;

	// Codificacao por DIFERENCA
	if(flag_diferenca == 1){
		//currentSize = diferenca_encoder(currentData, currentSize);
	}

	// Codificacao por CARREIRA
	if(flag_carreira == 1){
		//currentSize = carreira_encoder(currentData, currentSize);
	}

	// Codificacao por HUFFMAN
	if(flag_huffman == 1){
		//currentSize = huffman_encoder(currentData, currentSize);
	}

	// Juntandoo header com os dados do audio comprimido
	short * finalBuffer;
	currentSize = merge_header(&finalBuffer, header, currentData, currentSize, 44);

	// Escrevendo a stream de dados no arquivo passado como ultimo parametro
	write_bin(argv[argc-1], finalBuffer, currentSize);

	free(buffer);
	free(header);
	free(data);
	free(finalBuffer);
	

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

/*	int size = 16;

	short teste0[16] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 , 2};
	short teste1[16] = {1, 5, 4, 3, 8, 10, 127, 4, 7, 8, 9, 7, 15, 2, 1 , 3};
	short teste2[16] = {-1, -5, -4, -3, -8, -10, -16, -4, -7, -8, -9, -7, -15, -2, -1 , -3};
	short teste3[16] = {10, 50, 40, 30, 80, 100, 160, 40, 70, 80, 90, 70, 150, 20, 10 , 30};
	short teste4[16] = {-10, -50, -40, -30, -80, -100, -160, -40, -70, -80, -90, -70, -150, -20, -10 , -30};

	short * teste = teste1;

	int valormaximo = valor_maximo(teste, size);
	int min_bit = log_2((double)valormaximo);
	double result_size = ceil(size*min_bit/16.0) + 1.0;

	if(min_bit == 16) result_size = size;

	short * result = merge_bits(teste, size);

	for (i = 0; i < size; ++i){
		
		contador_bit_a_bit(teste[i], 16);

	}

	printf("\n");

	for (i = 0; i < result_size; ++i){
		
		contador_bit_a_bit(result[i], 16);

	}


	short * outroresult = extend_bits(result, result_size);

	printf("\n");

	for (i = 0; i < size; ++i){
		
		contador_bit_a_bit(outroresult[i], 16);

	}

	printf("\nvalormaximo = %d\nmin_bit = %d\n", valormaximo, min_bit);
	printf("diferentes = ");
	diferente(teste, outroresult, size);*/

	// --------------------- TESTANDO NEG MANAGER --------------------------------------------------------------------------------
/*
	short a = -15;
	short b = comp2_to_bit1(a, 8);

	short c = 15;
	short d = comp2_to_bit1(c, 8);

	contador_bit_a_bit(a, 16);
	contador_bit_a_bit(b, 16);
	contador_bit_a_bit(c, 16);
	contador_bit_a_bit(d, 16);

	short e = b;
	short f = bit1_to_comp2(e, 8);

	short g = d;
	short h = bit1_to_comp2(g, 8);

	contador_bit_a_bit(e, 16);
	contador_bit_a_bit(f, 16);
	contador_bit_a_bit(g, 16);
	contador_bit_a_bit(h, 16);
*/
	// --------------------- TESTANDO TIRAR HEADER -------------------------------------------------------------------------------


/*	short teste[16] = {10, 50, 40, 30, 80, 100, 160, 40, 70, 80, 90, 70, 150, 20, 10 , 30};

	short *header_test;
	short *data_test;

	int size_test = split_header(&header_test, &data_test, teste, 16, 4);

	printf("header\n");
	for(i = 0; i<4; i++)
		printf("%d\n", header_test[i]);

	printf("data\n");
	for(i = 0; i<size_test; i++)
		printf("%d\n", data_test[i]);*/



	return 0;
}
