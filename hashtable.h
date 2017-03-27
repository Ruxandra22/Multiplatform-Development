/*
 * Osman Maria - Ruxandra
 * Grupa 334CA
 */
#include <stdio.h>
#include <stdlib.h>

#include "bucket.h"

#ifndef HASHTABLE_H
#define HASHTABLE_H

typedef struct hashtable {
	bucket_pointer *bucket;
	int size;
} hashtable;

/* Functiile pentru hashtable */
hashtable *create_hashtable(int hash_size);

void destroy_hash(hashtable **DH);

void add(hashtable **h, char *word);

int find(hashtable *h, char *word);

void remove_hash(hashtable **h, char *word);

void print_hash(hashtable **hash);

void print_hash_file(hashtable **hash, FILE *fp);

void clear(hashtable **hash);

hashtable *resize(hashtable **hash, int size);

#endif
