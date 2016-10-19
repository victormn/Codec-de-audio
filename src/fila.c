#include "fila.h"
#include "huffman.h"

#include <stdio.h>
#include <stdlib.h>

/* Inicia uma nova fila */
void inicia(fila *f){

	f->prox = NULL;
}

/* Verifica se a fila esta vazia */
int vazia(fila *f){

	if(f->prox == NULL)
		return 1;
	else
		return 0;
}

/* Cria um elemento para a fila*/
fila *novo_elemento(node *no){

	fila *elemento = (fila *) malloc(sizeof(fila));
	if(elemento == NULL){
		printf("Erro ao criar um elemento para a fila!\n");
		exit(1);
	}else{
		elemento->no = no;
		return elemento;
	}
}

/* Pop na fila */
node *remove_item(fila *f){

	if(f->prox == NULL){
		return NULL;
	}else{
		fila *tmp = f->prox;
		f->prox = tmp->prox;

		return tmp->no;
	}

}

/* Free na fila */
void free_fila(fila *f){

	fila *next, *current;

	if(vazia(f) == 0){

		current = f->prox;

		while(current != NULL){

			next = current->prox;
			free(current);
			current = next;
		}
	}
}

void insere(fila *f, node *no){

	fila *novo = novo_elemento(no);
	novo->prox = NULL;

	if(vazia(f) == 1)
		f->prox=novo;
	else{
		fila *tmp = f->prox;

		while(tmp->prox != NULL)
			tmp = tmp->prox;

		tmp->prox = novo;
	}
}