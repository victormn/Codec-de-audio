#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura que ira armazenar o arquivo de audio lido (referencias no final do arquivo)
typedef struct  WAV_HEADER{
    char                RIFF[4];        // RIFF Header      Magic header
    unsigned int        ChunkSize;      // RIFF Chunk Size  
    char                WAVE[4];        // WAVE Header      
    char                fmt[4];         // FMT header       
    unsigned int        Subchunk1Size;  // Size of the fmt chunk                                
    unsigned short      AudioFormat;    // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM 
    unsigned short      NumOfChan;      // Number of channels 1=Mono 2=Sterio                   
    unsigned int        SamplesPerSec;  // Sampling Frequency in Hz                             
    unsigned int        bytesPerSec;    // bytes per second 
    unsigned short      blockAlign;     // 2=16-bit mono, 4=16-bit stereo 
    unsigned short      bitsPerSample;  // Number of bits per sample      
    char                Subchunk2ID[4]; // "data"  string   
    unsigned int        Subchunk2Size;  // Sampled data length    

} wav_hdr; 


// Faz a leitura de um arquivo wave
// Retorna o tamanho do arquivo, caso lido com sucesso
int read_wave(char const *arg) {

    FILE *f;    
    int headerSize = sizeof(wav_hdr);
    int fileSize = 0;
    wav_hdr header;

    // Verificando se foi possivel abrir o arquivo
    f = fopen(arg, "r");
    if(f == NULL) {
        printf("\nErro:\nNao foi possivel abrir o arquivo '%s'\n\n", arg);
        return EXIT_FAILURE;
    }

    // Lendo o arquivo
    fread(&header, headerSize, 1, f);

    // Obtendo o tamanho do arquivo
    fseek(f, 0, SEEK_END);
    fileSize = ftell(f);
    fseek(f, 0, SEEK_SET);

    fclose(f);

    return fileSize;
}

int main(int argc, char const *argv[]){
	
	FILE *f;
    int fileSize = 0;

	// Flags para saber quais metodos de codificacao serao utilizados
	int flag_diferenca = 0, flag_carreira = 0, flag_huffman = 0;

    // Verificando parametros de entrada
	if(argc < 3){
		printf("\nErro:\nUtilize: ./encoder -d -c -h <entrada.wav> <saida.bin>\n");
		printf("As flags -d -c -h sao opcionais e podem ser inseridas em qualquer ordem\n\n");
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

    // Lendo o arquivo WAVE (penultimo parametro)
    fileSize = read_wave(argv[argc-2]);

    printf("%d\n", fileSize);

	return 0;
}

// *** Referencias *** 
// http://soundfile.sapp.org/doc/WaveFormat/
// http://stackoverflow.com/questions/13660777/c-reading-the-data-part-of-a-wav-file