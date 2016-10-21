#ifndef HUFFMAN_H_
#define HUFFMAN_H_


typedef struct huffPair{
	short symbol;
	double frequency;
}huffPair;

struct Node{
	short symbol;
	double frequency;
	int edge;
	int parent;
	struct Node* left;
	struct Node* right;
	int id;
};

typedef struct Node node;

typedef struct huffCode{
	short symbol;
	int code;
	int *parent;
	int num_bit;
}huffCode;

typedef struct codedPair{
	short symbol;
	int code;
	short num_bit;
}codedPair;

huffPair* ordena_hvetor(huffPair *hvet, int size, int nsym);

node* ordena_nvetor(node* nos, node no, int size, int num_nos);

node* cria_arvore(huffPair* ordered_hvet, int size);

void forma_codigo(huffCode* codigo, int i, int aux, int tam_arvore);

int* buscar_pai(node* arvore, int* parent, int i, int j, int last);

int* numero_bits(node* arvore, int* nbits, int i, int j, int tam_arvore);

huffCode* busca_codigo(node* arvore, int tam_arvore);

int num_simbolos(short *buffer, int size);

int huffman_encoder(short ** result, short *buffer, int size);

int merge_data_w_header(short* data, short *vetor, short *pai, int num_elementos, int data_size, short ** result, int size, int n_bits);

int merge_datas(int* file, short ** result, int size, int *n_bits);

void create_header(node * arvore, int num_elementos, int ** vetor, int ** pai);

void expand_data_n_header(short * file, short **vetor, short **pai, short **data, int file_size, int *n_bits, int *num_elementos, int *original_size);

int next_bit(short *entrada, int i, int j);

short busca_simbolo(short *data, short *vetor, short *pai, int pos, int *i, int *j, int bit, int *aux_n_bits);

int huffman_decoder(short ** result, short *file, int file_size);

#endif