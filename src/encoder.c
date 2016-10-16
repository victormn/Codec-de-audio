// 
//  Trabalho 1 - Codec de Audio
//
//  Alunos:
//      Elisa Jorge Marcatto        nUSP 7961965
//      Victor Marcelino Nunes      nUSP 8622381
//

#include "file_manager.h"
#include "bit_manager.h"
#include "carreira.h"
#include "diferenca.h"
//#include "huffman.h"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "testes.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){
	
	int currentSize = 0, originalSize = 0, i;
    short *buffer, *currentData, *header, *data, *diferenca, *carreira, *huffman, *headerMerged, *flagMerged, *compress;

	// Flags para saber quais metodos de codificacao serao utilizados
	int flag_diferenca = 0, flag_carreira = 0, flag_huffman = 0;

	// Verificando parametros de entrada
	if(argc < 3 || argc > 6){
		printf("! Erro ! Numero de argumentos errado !\n\nUtilize: ./encode -d -c -h <entrada.wav> <saida.bin>\n");
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
	originalSize = read_wave(argv[argc-2], &buffer);
	currentSize = originalSize;

	// Current data sempre ira receber os valores do vetor de short que sera trabalhado
	currentData = buffer;

	// Separando o header dos dados do audio
	currentSize = split_header(&header, &data, buffer, currentSize, 44);
	currentData = data;

	// Codificacao por DIFERENCA
	if(flag_diferenca == 1){

		diferenca = diferenca_encoder(currentData, currentSize);
		currentData = diferenca;

	}

	// Codificacao por CARREIRA
	if(flag_carreira == 1){

		currentSize = carreira_encoder(&carreira, currentData, currentSize);
		currentData = carreira;

	}

	// Codificacao por HUFFMAN
	if(flag_huffman == 1){

	}

	// Comprimindo o arquivo
	currentSize = merge_bits(&compress, currentData, currentSize);
	currentData = compress;

	// Juntandoo header com os dados do audio comprimido
	currentSize = merge_header(&headerMerged, header, currentData, currentSize, 44);
	currentData = headerMerged;

	//Colocando quais metodos de compressao foram utilizados
	currentSize = merge_compress_flags(&flagMerged, currentData, currentSize, flag_diferenca, flag_carreira, flag_huffman);
	currentData = flagMerged;

	// Escrevendo a stream de dados no arquivo passado como ultimo parametro
	write_bin(argv[argc-1], currentData, currentSize);

	printf("Comprimido com sucesso!\nTaxa de Compressao = %.2f%%\n", (1.0 - ((double)currentSize)/((double)originalSize))*100.0);

	free(buffer);
	free(header);
	free(data);
	free(headerMerged);
	free(flagMerged);
	free(compress);

	if(flag_diferenca == 1) free(diferenca);

	if(flag_carreira == 1) free(carreira);

	//if(flag_huffman == 1) free(huffman);

	return 0;
}
