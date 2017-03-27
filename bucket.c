/*
 * Osman Maria - Ruxandra
 * Grupa 334CA
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bucket.h"

bucket_list *create_cell(char *word)
{
    /* Capatul listei */
	bucket_list *head;

	head = malloc(sizeof(bucket_list));
	head->next = NULL;
	head->word = malloc(sizeof(char) * (strlen(word) + 1));
	memcpy(head->word, word, strlen(word) + 1);
	/* Verificam daca s-a alocat corect memorie */
	if (head == NULL) {
		fprintf(stderr, "out of memory\n");
		exit(-1);
	}
	return head;
}

/* Printeaza lista de la un anumit nod incolo */
int print_bucket(bucket_list **head)
{
	bucket_list *current_node = *head;

	if (*head == NULL)
		return 0;
	while (current_node != NULL) {
		if (current_node->word != NULL)
			printf("%s ", current_node->word);
		current_node = current_node->next;
	}
	return 1;
}

void print_bf(bucket_list **head, FILE *fp)
{
	bucket_list *current_node;

	if (*head == NULL)
		return;
	current_node = *head;
	while (current_node != NULL) {
		if (current_node->word != NULL)
			fprintf(fp, "%s", current_node->word);
		if (current_node->next != NULL)
			fprintf(fp, "%s", " ");
		current_node = current_node->next;
	}
	fprintf(fp, "%s", "\n");
}

/* Adaugam un element la finalul listei */
void push(bucket_list **head, char *word)
{
	bucket_list *current;
	bucket_list *p;

	current = create_cell(word);
	p = *head;
	if ((*head) == NULL)
		*head = current;
	else {
		/*
		 * parcurgem lista pana cand
		 * gasim un element NULL
		 * => am ajuns la final
		 */
		while (p->next != NULL)
			p = p->next;
		p->next = current;
	}
}

void remove_list(bucket_list **node, char *word)
{

	bucket_list *auxiliary_pointer;
	bucket_list *pointer;

	pointer = *node;
	/* daca lista este goala */
	if (*node == NULL)
		return;

	if (strcmp((*node)->word, word) == 0) {
		/* daca nu e singurul element din lista */
		if ((*node)->next != NULL) {
			(*node) = (*node)->next;
			free(pointer->word);
			free(pointer);
			pointer = NULL;
			return;
		}
		/* daca este primul si ultimul element din lista */
		free((*node)->word);
		free(*node);
		*node = NULL;
		return;
	}

	while (pointer->next != NULL) {
		/* daca cuvantul este in ultimul nod din lista */
		if (pointer->next->next == NULL) {
			if (strcmp(pointer->next->word, word) == 0) {
				auxiliary_pointer = pointer->next;
				free(auxiliary_pointer->word);
				free(auxiliary_pointer);
				auxiliary_pointer = NULL;
				pointer->next = NULL;
				return;
			}
		}
		/* daca este un cuvant din interiorul listei */
		if (strcmp(pointer->next->word, word) == 0) {
			auxiliary_pointer = pointer->next;
			if (auxiliary_pointer->next == NULL) {
				free(auxiliary_pointer->word);
				free(auxiliary_pointer);
				auxiliary_pointer = NULL;
				pointer->next = NULL;
			} else {
				pointer->next = auxiliary_pointer->next;
				free(auxiliary_pointer->word);
				free(auxiliary_pointer);
				auxiliary_pointer = NULL;
			}
		}
		/* avansam in lista */
		pointer =  pointer->next;
	}
}

void destroy_bucket(bucket_list **BD)
{
	bucket_list *copy;
	bucket_list *aux;

	copy = *BD;
	aux = copy;
	while (copy != NULL) {
		aux = copy;
		copy = copy->next;
		free(aux->word);
		free(aux);
	}
	*BD = NULL;
}
