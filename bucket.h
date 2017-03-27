/*
 * Osman Maria - Ruxandra
 * Grupa 334CA
 */
#include <stdio.h>
#include <stdlib.h>

#ifndef BUCKET_H
#define BUCKET_H


/* lista pentru cuvinte*/
typedef struct list {
	char *word;
	struct list *next;
} bucket_list, *bucket_pointer, **bucket_destroy;

bucket_list *create_list(void);

int print_bucket(bucket_list **head);

void print_bf(bucket_list **head, FILE *fp);

void push(bucket_list **head, char *word);

void remove_list(bucket_list **node, char *word);

void destroy_bucket(bucket_destroy BD);

#endif
