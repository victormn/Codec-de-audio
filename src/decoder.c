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
	
	int currentSize = 0, num_channels = 0;
    short *buffer, *currentData, *header, *data, *diferenca, *carreira, *headerMerged, *flagRemoved, *decompress, *mergeChannels;

	// Flags para saber quais metodos de codificacao serao utilizados
	int flag_diferenca = 0, flag_carreira = 0, flag_huffman = 0;

	// Verificando parametros de entrada
	if(argc != 3){
		printf("! Erro ! Numero de argumentos errado !\n\nUtilize: ./decode <entrada.bin> <saida.wav>\n");
		return EXIT_FAILURE;
	}

	// Lendo o arquivo BIN (penultimo parametro)
	currentSize = read_wave(argv[argc-2], &buffer);

	// Verificando quais metodos de codificacao serao utilizados
	if(((buffer[0] >> 2) & 1) == 1) flag_diferenca = 1;
	if(((buffer[0] >> 1) & 1) == 1) flag_carreira = 1;
	if(((buffer[0]     ) & 1) == 1) flag_huffman = 1;

	// Removendo o header das flags
	currentSize = remove_compress_flags(&flagRemoved, buffer, currentSize);
	currentData = flagRemoved;

	// Separando o header dos dados do audio
	currentSize = split_header(&header, &data, currentData, currentSize, 22);
	currentData = data;

	// Descomprimindo o arquivo
	currentSize = extend_bits(&decompress, currentData, currentSize);
	currentData = decompress;

	// Decodificar por HUFFMAN
	if(flag_huffman == 1){

	}

	// Decodificar por CARREIRA
	if(flag_carreira == 1){

		currentSize = carreira_decoder(&carreira, currentData, currentSize);
		currentData = carreira;

	}

	// Decodificar por DIFERENCA
	if(flag_diferenca == 1){

		diferenca = diferenca_decoder(currentData, currentSize);
		currentData = diferenca;

	}

	// Considerando o numero de canais
	num_channels = buffer[12];
	if(num_channels == 2){
		mergeChannels = merge_channels(currentData, currentSize);
		currentData = mergeChannels;
	}

	// Juntandoo header com os dados do audio comprimido
	currentSize = merge_header(&headerMerged, header, currentData, currentSize, 22);
	currentData = headerMerged;

	// Escrevendo a stream de dados no arquivo passado como ultimo parametro
	write_bin(argv[argc-1], currentData, currentSize);

	printf("Descomprimido com sucesso!\n");

	free(buffer);
	free(header);
	free(data);
	free(headerMerged);
	free(flagRemoved);
	free(decompress);
	free(mergeChannels);

	if(flag_diferenca == 1) free(diferenca);

	if(flag_carreira == 1) free(carreira);

	//if(flag_huffman == 1) free(huffman);

	return 0;
}
