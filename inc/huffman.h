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
	short code;
	int *parent;
	int num_bit;
}huffCode;

typedef struct codedPair{
	short symbol;
	short code;
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

short * merge_data_w_header(short* data, short *vetor, short *pai, int num_elementos, int data_size);

int merge_datas(short* file, short ** result, int size);

void create_header(node * arvore, int num_elementos, int ** vetor, int ** pai);

void expand_data_n_header(short * file, int **vetor, int **pai, int **data, int file_size, int *data_size, int *num_elementos);

void print_arvore(node *arvore, int size);

int next_bit(short *entrada, int i, int j);

short busca_simbolo(short *entrada, short *vetor, int pos, int nsym, int i, int j, int bit, int *pai);

#endif