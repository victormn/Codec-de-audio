#include "huffman.h"
#include "bit_manager.h"
#include "fila.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

// Funcoes auxiliares para a codificacao

// Ordena o vetor de 'huffPair' com base na frequencias dos simbolos
huffPair* ordena_hvetor(huffPair *hvet, int size){

	int i, j, k;
	double aux_f;
	short aux_s;
	huffPair *ordered = calloc(size,sizeof(huffPair));	

	k = 0;
	
	for(i=0; i<size; i++){
		if(hvet[i].frequency != 0){
			ordered[k].symbol = hvet[i].symbol;
			ordered[k].frequency = hvet[i].frequency;
			k++;
		}
	}	

	for(i=k-1; i>=1; i--){
		for(j=0; j<i; j++){
			if(ordered[j].frequency >= ordered[j+1].frequency){
				aux_f = ordered[j].frequency;
				aux_s = ordered[j].symbol;
				ordered[j].frequency = ordered[j+1].frequency;
				ordered[j].symbol = ordered[j+1].symbol;
				ordered[j+1].frequency = aux_f;
				ordered[j+1].symbol = aux_s;
			}
		}
	}

	return ordered;
}

// Ordena o vetor de 'node' com base na frequencia de cada no
// Essa ordenacao procura qual o local que o novo elemento deve ser inserido
//e reajusta o vetor com base nessa posicao
void ordena_nvetor(node* nos, node no, int size, int num_nos, node ** result){

	int i;
	int k;
	node *ordered = calloc(num_nos,sizeof(node));	

	for(i=0; i<size; i++){
		if(no.frequency < nos[i].frequency){
			k = i;
			
			ordered[i] = no;
			break;
		}
		else{
			k = size;
			ordered[k] = no;
		}
	}	

	if(k == size){
		for(i=0; i<k+1; i++){
			ordered[i] = nos[i];
		}
	}
	else{
		for(i=0; i<k; i++){
			ordered[i] = nos[i];
		}

		for(i=k+1; i<(size+1); i++){
			ordered[i] = nos[i-1];
		}	
	}

	for(i = 0; i<num_nos; i++)
		*(*result+i) = ordered[i];

	free(ordered);

} 

// Monta arvore de Huffman
node* cria_arvore(huffPair* ordered_hvet, int size){

	int i, id, num_nos;

	id = 1;

	// O numero de nos da arvore eh dado por: (2*numero_de_simbolos)+1
	num_nos = (2*size)-1;
	
	node *nos = calloc(sizeof(node),num_nos);

	for(i=0; i<size; i++){																												
		nos[i].frequency = ordered_hvet[i].frequency;
		nos[i].symbol = ordered_hvet[i].symbol;
		nos[i].left = NULL;
		nos[i].right = NULL;

		// Para quando o no for no folha
		nos[i].id = 0;

	}

	for(i=0; i<num_nos-1; i+=2){

		nos[size].frequency = nos[i].frequency + nos[i+1].frequency;
		nos[size].edge = -1;
		nos[size].parent = -1;
		nos[size].left = &nos[i];
		nos[size].right = &nos[i+1];
		nos[size].id = id;
		nos[size].symbol = -100;

		nos[i].edge = 0;
		nos[i].parent = id;

		nos[i+1].edge = 1;
		nos[i+1].parent = id;	

		ordena_nvetor(nos, nos[size], size, num_nos, &nos);		

		size++;
		id++;	

	}

	return nos;		
}

// Constroi o codigo do simbolo
void forma_codigo(huffCode* codigo, int i, int aux, int tam_arvore){

	int j;
	
	for(j=0; j<codigo[i].num_bit; j++){
		if(codigo[i].parent[j] == 0){
			codigo[i].code += 0; 
			aux--;		
		}
		else{
			codigo[i].code += (int)pow(2,aux);
			aux--;
		}			
	}
}

// Busca pelo pai de cada no, obtendo o codigo de cada simbolo (armazenado em '*parent')
int* buscar_pai(node* arvore, int* parent, int i, int j, int last){

	if(i != j && arvore[i].parent == arvore[j].id){
		if(arvore[j].parent == -1){
			return parent;
		}
		else{

			parent[last] = arvore[j].edge;	
			last--;
			buscar_pai(arvore, parent, j, j+1, last);
		}
	}
	else{
			buscar_pai(arvore, parent, i, j+1, last);
	}

	return NULL;	
}

// Retorna em *nbits o numero de bits que cada simbolo precisa para representar
//seu codigo
void numero_bits(node* arvore, int* nbits, int i, int j, int tam_arvore){
	
	int k;	

	for(k=0; k<tam_arvore; k++){		
		if(arvore[j].parent == arvore[k].id){
			nbits[i]++;
			numero_bits(arvore, nbits, i, k, tam_arvore);
		}
	}

}

// Obtem o codigo de cada simbolo
huffCode* busca_codigo(node* arvore, int tam_arvore){

	int i, aux;
	int *nbits;

	huffCode *codigo = calloc(sizeof(huffCode),tam_arvore); 
	nbits = (int*)calloc(sizeof(int),tam_arvore);	
	
	for(i=0; i<tam_arvore; i++){
		numero_bits(arvore, nbits, i, i, tam_arvore);
		codigo[i].num_bit = nbits[i];	
		codigo[i].parent = (int*)calloc(codigo[i].num_bit, sizeof(int));			
	}

	for(i=0; i<tam_arvore; i++){
		if(arvore[i].parent == -1){
			if((codigo[i].num_bit) > 0){
				//No raiz
				codigo[i].parent[(codigo[i].num_bit)-1] = -1;
			}
		}
		else{
			// Demais nos
			codigo[i].parent[(codigo[i].num_bit)-1] = arvore[i].edge;
			buscar_pai(arvore, codigo[i].parent, i, 0, (codigo[i].num_bit)-2);
		}
	}		
	
	for(i=0; i<tam_arvore; i++){
		aux = (codigo[i].num_bit)-1;
		forma_codigo(codigo, i, aux, tam_arvore);

		if(arvore[i].id != 0){
			codigo[i].symbol = -1;
		}
		else codigo[i].symbol = arvore[i].symbol;
	}	

	free(nbits);

	return codigo;
}

// Retorna no numero de simbolos da arvore
int num_simbolos(short *buffer, int size){

	int i, j, nsym;
	int check[size];

	for(i=0; i<size; i++){
		check[i] = 0;
	}

	for(i=0; i<size; i++){

		// O simbolo ainda nao pode ter sido analisado para que sua frequencia seja atualizada
		if(check[i] == 0){
			nsym++;
			
			for(j=0; j<size; j++){
				if(i != j && buffer[i] == buffer[j]){
					check[j] = 1;
				}
			}
			check[i] = 1;			
		} 		
	}

	return nsym;
}

// Cria os vetores para o header para a codificacao. Sendo eles:
// - Um vetor que cada posicao indica qual a posicao de seu primeiro filho ou qual seu simbolo, em caso de no folha
// - Um vetor que indica se a posicao correspondente no vetor descrito acima é de um no pai ou folha
void create_huffheader(node * arvore, int num_elementos, short ** vetor, short ** pai){

	int i,child_aux;

	*vetor = (short*) calloc (num_elementos, sizeof(short));
	*pai = 	(short*) calloc (num_elementos, sizeof(short));

	fila *q = (fila*) calloc (1, sizeof(fila));

	inicia(q);
	insere(q, &arvore[num_elementos-1]); /* Inserindo o no raiz */

	child_aux = 1;

	for(i = 0; vazia(q) == 0; i++){

		node *current = remove_item(q);

		if(current->left != NULL)
			insere(q, current->left);
		else child_aux--;

		if(current->right != NULL)
			insere(q, current->right);
		else child_aux--;

		if(current->id == 0)
			*(*vetor+i) = current->symbol;
		else{
			*(*pai+i) = 1;
			*(*vetor+i) = i*2+child_aux;
		}
	}

	free(q);
}

// Faz um merge nos codigos de cada simbolo, levando em conta a quantidade
//de bits necessaria para representa-los
int merge_datas(int* file, short ** result, int size, int *n_bits){

	short *aux;
	int result_size, i, j, k, current_bit, ptr, shift, bit, aux_count, n_bits_aux;

	aux = (short*) calloc (size, sizeof(short));

	current_bit = file[0];
	ptr = 1;
	aux_count = 16;
	i = 0;
	result_size = 1;
	n_bits_aux = 0;

	for(j = 1; j < size; j+=2){

		// file[j] = codigo
		// file[j+1] = quantidade de bits do proximo codigo 
		// current_bit = quantidade de bits do codigo atual

		for(k = current_bit-1; k >= 0; k--){

			if(aux_count == 0){
				i++;
				aux_count = 16;
				ptr = 1;

				result_size++;
			}

			bit = (file[j] >> k) & 1;
			shift = 16 - ptr;
			ptr++;
			aux[i] = aux[i] | (bit << shift);
			aux_count--;
			n_bits_aux++;

		}

		current_bit = file[j+1];

	}

	*result = (short*) calloc (result_size, sizeof(short));

	for(i = 0; i<result_size; i++){

		*(*result+i) = aux[i];

	}

	free(aux);

	*n_bits = n_bits_aux;

	return result_size;

}

// Junta o header com os dados codificados. O Header possui:
// - Numero de elementos da arvore
// - Tamanho original do arquivo
// - Numero de bits do arquivo final
// - Um vetor que cada posicao indica qual a posicao de seu primeiro filho ou qual seu simbolo, em caso de no folha
// - Um vetor que indica se a posicao correspondente no vetor descrito acima é de um no pai ou folha
int merge_data_w_header(short* data, short *vetor, short *pai, int num_elementos, int data_size, short ** result, int size, int n_bits){

	int size_result, i, j;
	short *aux;

	size_result = 5 + 2*(num_elementos) + data_size;

	*result = (short*) calloc (size_result, sizeof(short));
	aux = (short*) calloc (size_result, sizeof(short));

	aux[0] = num_elementos;
	aux[1] = (size >> 16) & 0xffff;
	aux[2] = size & 0xffff;
	aux[3] = (n_bits >> 16) & 0xffff;
	aux[4] = n_bits & 0xffff;

	for(i = 0; i < num_elementos; i++)
		aux[i+5] = vetor[i];
	for(i = num_elementos + 5, j = 0; j < num_elementos; i++, j++)
		aux[i] = pai[j];
	for(i = 0, j = 5 + 2*(num_elementos); i < data_size; i++, j++)
		aux[j] = data[i];

	for(i=0; i<size_result; i++){

		*(*result+i) = aux[i];
	}

	free(aux);

	return size_result;
}

// Realiza a codificao Huffman
int huffman_encoder(short ** result, short *buffer, int size){

	// Cada posicao do vetor 'buffer' representa um simbolo a ser analisado na codificacao Huffman
	int i, j, nsym, data_size, result_size, n_bits, tam_arvore;	
	int k = 0;
	int *check, *huff;
	short *result1, *vetor, *pai; 
	huffPair *hvet, *ordered_hvet;
	huffCode *codigo;
	node *arvore;

	check = (int*)calloc(sizeof(int),(size + 1));
	huff = (int*)calloc(sizeof(int),(2*size + 1));

	hvet = calloc(sizeof(huffPair),size);
	nsym = 0;

	for(i=0; i<size; i++){

		// Existe pelo menos uma ocorrencia de cada simbolo
		hvet[i].frequency = 1;
		// Nenhum simbolo  ainda foi analisado
		check[i] = 0;
	}

	for(i=0; i<size; i++){		

		// O simbolo ainda nao pode ter sido analisado para que sua frequencia seja atualizada
		if(check[i] == 0){
			nsym++;
			for(j=0; j<size; j++){
				if(i != j && buffer[i] == buffer[j]){
					hvet[i].frequency++;
					check[j] = 1;
				}
			}
			check[i] = 1;
			hvet[i].symbol = buffer[i];
		} 
		else{
			hvet[i].frequency = 0;		
		}
	}

	for(i=0; i<size; i++){
		hvet[i].frequency = (hvet[i].frequency)/size;
	}

	// Manipulando frequencias
	ordered_hvet = ordena_hvetor(hvet, size);		

	// Manipulando arvore	
	arvore = cria_arvore(ordered_hvet, nsym);    

	// Manipulando codigos
	tam_arvore = (2*nsym)-1;
	codedPair *coded = calloc(sizeof(codedPair),nsym);
	codigo = busca_codigo(arvore, tam_arvore);	

	int r = 0;

	for(i=0; i<tam_arvore; i++){

		if(codigo[i].symbol != -1){

			coded[r].symbol = codigo[i].symbol;
			coded[r].code = codigo[i].code;
			coded[r].num_bit = codigo[i].num_bit;
			r++;

		}
	}		

	for(i=0; i<size; i++){
		for(j=0; j<nsym; j++){
			if(buffer[i] == coded[j].symbol){

				huff[k] = coded[j].num_bit;
				k++;
				huff[k] = coded[j].code;
				k++;

			}
		}
	}

	data_size = merge_datas(huff, &result1, 2*size, &n_bits);
	create_huffheader(arvore, tam_arvore, &vetor, &pai);
	result_size = merge_data_w_header(result1, vetor, pai, tam_arvore, data_size, result, size, n_bits);

	free(check);
	free(ordered_hvet);
	free(arvore);
	for(i = 0; i<tam_arvore; i++)
		free(codigo[i].parent);
	free(codigo);
	free(coded);
	free(vetor);
	free(pai);
	free(result1);
	free(huff);
	free(hvet);

	return result_size;
}

// Funcoes auxiliares para a decodificacao

// Filtra as informacoes do header
void expand_data_n_header(short * file, short **vetor, short **pai, short **data, int file_size, int *n_bits, int *num_elementos, int *original_size){

	int i, j, aux, data_size, n;

	*num_elementos = file[0];
	*original_size = ((file[1] << 16) & 0xffff0000) | (file[2] & 0xffff);
	*n_bits = ((file[3] << 16) & 0xffff0000) | (file[4] & 0xffff);

	n = *num_elementos;

	data_size = file_size - 5 - 2*(file[0]);

	*vetor = (short*) calloc (n, sizeof(short));
	*pai = (short*) calloc (n, sizeof(short));
	*data = (short*) calloc (data_size, sizeof(short));

	aux = 5 + 2*n;

	for(i = 0; i < n; i++)
		*(*vetor+i) = file[i+5];
	for(i = n + 5, j = 0; j < n; i++, j++)
		*(*pai+j) = file[i];
	for(i = 0, j = aux; i < data_size; i++, j++)
		*(*data+i) = file[j];

}

// Retorna o proximo bit de um dado vetor
int next_bit(short *data, int i, int j){
	return ((data[i] >> j) & 1);
}

// A partir do codigo, busca o simbolo correspondente
short busca_simbolo(short *data, short *vetor, short *pai, int pos, int *i, int *j, int bit, int *aux_n_bits){

	if(pai[pos] == 0)
		return vetor[pos];

	*(j) = *j - 1;
	*(aux_n_bits) = *aux_n_bits + 1;

	if(*j<0){
		*(i) = *i + 1;
		*(j) = 15;
	}

	if(bit == 0)
		pos = vetor[pos];
	else
		pos = vetor[pos]+1;

	return busca_simbolo(data, vetor, pai, pos, i, j, next_bit(data, *i, *j), aux_n_bits);

}

// Faz a decodificacao de huffman
int huffman_decoder(short ** result, short *file, int file_size){

	short *vetor, *pai, *data;
	int n_bits, num_elementos, original_size, aux_n_bits, i, j, x;

	aux_n_bits = 0;
	i = 0;
	j = 15;

	expand_data_n_header(file, &vetor, &pai, &data, file_size, &n_bits, &num_elementos, &original_size);

	*result = (short*) calloc (original_size+1, sizeof(short));

	for(x = 0; aux_n_bits <= n_bits; x++){

		*(*result+x) = busca_simbolo(data, vetor, pai, 0, &i, &j, next_bit(data, i, j), &aux_n_bits);
	}	

	free(vetor);
	free(pai);
	free(data);

	return original_size;

}

