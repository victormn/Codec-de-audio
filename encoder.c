#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]){

	// Flags para saber quais metodos de codificacao serao utilizados
	int flag_diferenca = 0, flag_carreira = 0, flag_huffman = 0;

	if(argc < 3){
		printf("\nUtilize: ./encoder -d -c -h <entrada.wav> <saida.bin>\n\n");
		printf("\nAs flags -d -c -h sao opcionais e podem ser inseridas em qualquer ordem\n\n");
		return EXIT_FAILURE;
	}

	// Verificando a opcao utilizada
	// obs: como o numero minimo de argumentos estabelecido foi 3, deve-se verificar se ha mais que 3 argumentos
	//antes de verificar o argv[3]
	if(strcmp (argv[1], "-d") == 0 || strcmp (argv[2], "-d") == 0 || (argc > 3 && strcmp (argv[3], "-d") == 0))
		flag_diferenca = 1;

	if(strcmp (argv[1], "-c") == 0 || strcmp (argv[2], "-c") == 0 || (argc > 3 && strcmp (argv[3], "-c") == 0))
		flag_carreira = 1;

	if(strcmp (argv[1], "-h") == 0 || strcmp (argv[2], "-h") == 0 || (argc > 3 && strcmp (argv[3], "-h") == 0))
		flag_huffman = 1;

	printf("%d %d %d\n", flag_diferenca, flag_carreira, flag_huffman);

	return 0;
}