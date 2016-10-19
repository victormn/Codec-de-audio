#ifndef FILA_H_
#define FILA_H_

#include "huffman.h"

struct Fila{

	node *no;
	struct Fila *prox;

};
typedef struct Fila fila;

void inicia(fila *f);
int vazia(fila *f);
fila *novo_elemento(node *no);
node *remove_item(fila *f);
void free_fila(fila *f);
void insere(fila *f, node *no);

#endif