/*
 * Osman Maria - Ruxandra
 * Grupa 334CA
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtable.h"
#include "bucket.h"
#include "hash.h"

hashtable *create_hashtable(int hash_size)
{

	int i;
	hashtable *h = NULL;

	h = malloc(sizeof(hashtable));
	/* Setam dimensiunea hashtable-ului */
	h->size = hash_size;
	h->bucket = malloc(hash_size * sizeof(bucket_pointer));

	for (i = 0; i < hash_size; i++)
		h->bucket[i] = NULL;
	return h;
}

void destroy_hash(hashtable **DH)
{

	bucket_list *aux;
	int i;

	for (i = 0; i < (*DH)->size; i++) {
		aux = (*DH)->bucket[i];
		destroy_bucket(&aux);
	}

	free((*DH)->bucket);
	free(*DH);
	*DH = NULL;
}


void clear(hashtable **hash)
{
	int i;

	for (i = 0; i < (*hash)->size; i++)
		destroy_bucket((*hash)->bucket + i);
}

/* Functie care verifica daca un cucant exista sau nu in hashtable */
int find(hashtable *h, char *word)
{
	unsigned int index;
	bucket_list *current;

	/* Luam lista de la indexul respectiv */
	index = hash(word, h->size);
	current = h->bucket[index];
	/* Daca se gaseste ceva in lista */
	while (current != NULL) {
		/* Daca s-a gasit cuvantul */
		if (strcmp(current->word, word) == 0)
			return 1;
		current = current->next;
	}
	return 0;
}

/* Functie care adauga un cuvant nou in hashtable */
void add(hashtable **h, char *word)
{
	/* daca cuvantul este deja in hashtable, nu il mai adaugam */
	int n = find((*h), word);
	unsigned int index;

	if (n)
		return;

	index = hash(word, (*h)->size);
	push(((*h)->bucket + index), word);
}

void remove_hash(hashtable **h, char *word)
{

	int n = find((*h), word);
	unsigned int index;

	if (n) {
		index = hash(word, (*h)->size);
		remove_list(((*h)->bucket + index), word);
	}
}

hashtable *resize(hashtable **hash, int size)
{

	hashtable *new_hash;
	int i;
	bucket_list *bucket_aux;

	new_hash = create_hashtable(size);
	//printf("Dimensiunea noua in resize: %d\n", new_hash->size);
	for (i = 0; i < (*hash)->size; i++) {
		bucket_aux = (*hash)->bucket[i];
		/* cat timp gasim o lista care sa contina elemente */
		while (bucket_aux != NULL) {
			add(&new_hash, bucket_aux->word);
			bucket_aux = bucket_aux->next;
		}
	}
	destroy_hash(hash);
	return new_hash;
}

void print_hash(hashtable **hash)
{
	int i;
	int verify;

	if (hash == NULL)
		return;
	//printf("Hashtable: %d\n", (*hash)->size);
	for (i = 0; i < (*hash)->size; i++) {
		verify = print_bucket((*hash)->bucket + i);
		//printf("verify: %d\n", verify);
		if (verify == 1)
			printf("\n");
	}
}

void print_hash_file(hashtable **hash, FILE *fp)
{
	int i;

	for (i = 0; i < (*hash)->size; i++)
		print_bf((*hash)->bucket + i, fp);
}
