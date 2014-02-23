/**
  \file lista.c
  \brief Ejemplo de la aplicación de una lista.

   Codigo ejemplo del uso de una lista simplemente enlanzada.

   \author Oswaldo Arroyo
   \date   01/2014
*/

#include <stdlib.h>

typedef struct List {
	struct Node *first;
	unsigned int count;
} list;

typedef struct Node {
	unsigned int value;
	struct Node *next;
} node;

list * init_list(void);
node * create_node(int value);
int add(list *lista, int value);
int push(list *lista, int value);
int pop(list *lista);
int insert_after(list *lista, int s_value, int n_value);
void print_list(list *lista);
void destroy_list(list *lista);

int main(void) {

	list *lista;

	lista = init_list();
	if(lista == NULL) {
		fprintf(stderr,"Can't create de list");
		return -1;
	}

	push(lista,1);
	push(lista,2);
	push(lista,3);
	push(lista,4);

	insert_after(lista,3,10);

	printf("POP: %i\n",pop(lista));
	printf("POP: %i\n",pop(lista));

	print_list(lista);

	destroy_list(lista);
	return 0;
}

list * init_list(void) {	
	list *new_lista;
	new_lista = calloc(1,sizeof(list));
	return new_lista;
}

int add(list *lista, int value) {

	node *nodo;
	node *centinela;

	if(lista == NULL) return 0;

	nodo = create_node(value);
	if(nodo == NULL) return 0;

	if(lista->first == NULL) {
		lista->first = nodo;
		lista->count = 1;
		return 1;
	}

	centinela = lista->first;
	while(centinela->next!=NULL) {
		centinela = centinela->next;
	}

	centinela->next = nodo;
	lista->count++;

	return 1;
}

int push(list *lista, int value) {
	node *nodo;

	if(lista == NULL) return 0;

	nodo = create_node(value);
	if(nodo == NULL) return 0;

	if(lista->first == NULL) {
		lista->first = nodo;
		lista->count = 1;
		return 1;
	}

	nodo->next = lista->first;
	lista->first = nodo;

	return 1;
}

int pop(list *lista) {
	int value;
	node *nodo;

	if(lista == NULL) return -1;
	if(lista->first == NULL) return -1;

	nodo = lista->first;

	lista->first = nodo->next;
	lista->count--;

	value = nodo->value;

	free(nodo);

	return value;

}

node * create_node(int value) {
	node *nodo;

	nodo = calloc(1, sizeof(node));
	if(nodo == NULL) return NULL;

	nodo->value = value;
	nodo->next = NULL;

	return nodo;
}

void print_list(list *lista) {
	node *centinela;

	if(lista == NULL) return;
	centinela = lista->first;

	while(centinela != NULL) {
		printf("%i\n",centinela->value);
		centinela = centinela->next;
	}

	return;
}

void destroy_list(list *lista) {
	node *nodo;
	node *nodo2;

	if(lista == NULL) return;

	nodo = lista->first;
	while(nodo != NULL) {
		nodo2 = nodo;
		nodo = nodo->next;
		free(nodo2);
	}

	free(lista);
	return;
}

int insert_after(list *lista, int s_value, int n_value) {
	node *centinela;
	node *new_nodo;

	if(lista == NULL) return -1;
	if(lista->first == NULL) return -1;

	centinela = lista->first;

	while(centinela!=NULL) {
		if(centinela->value == s_value) {
			break;
		}

		centinela = centinela->next;
	}

	if(centinela == NULL) return -1;

	new_nodo = create_node(n_value);
	if(new_nodo == NULL) return -1;

	new_nodo->next = centinela->next;
	centinela->next = new_nodo;

	return 1;
}
