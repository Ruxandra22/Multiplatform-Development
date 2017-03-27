/*
 * Osman Maria - Ruxandra
 * Grupa 334CA
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parsecommand.h"
#include "hashtable.h"
#include "bucket.h"

#define BUFFERSIZE 20000

/* useful macro for handling error codes */
#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(EXIT_FAILURE);				\
		}							\
	} while (0)

void parse_command(char *line, FILE *fp, hashtable **hash)
{
	char *token, *command;
	char **tok;
	FILE *f;
	int index;
	bucket_list *list_p;
	int new_s;
	unsigned int i;
	int aux = 0;

	tok = malloc(3 * sizeof(char *));

	if (fp == NULL) {
		free(tok);
		return;
	}
	token = strtok(line, "\n ");
	command = token;
	if (command != NULL) {
		if (strcmp(command, "add") == 0) {
			tok[1] = strtok(NULL, "\n ");
			DIE(tok[1] == NULL, "Invalid command!");
			add(hash, tok[1]);
		} else if (strcmp(command, "remove") == 0)
			remove_hash(hash, strtok(NULL, "\n "));
		else if (strcmp(command, "find") == 0) {
			tok[1] = strtok(NULL, " ");
			tok[2] = strtok(NULL, "\n ");
			/*
			 * daca avem doar 2 parametri,
			 * scriem la consola
			 */
			if (tok[2] == NULL) {
				tok[1] = strtok(tok[1], "\n");
				/* verificam daca s-a gasit cuvantul */
				if (find(*hash, tok[1]) == 1)
					printf("True\n");
				else
					printf("False\n");
			} else if (tok[2] != NULL) {
				/*
				 * cazul in care avem 3 parametri,
				 * deci scriem in fisier
				 */
				f = fopen(tok[2], "a");
				if (find(*hash, tok[1]) == 1)
					fprintf(f, "%s", "True\n");
				else
					fprintf(f, "%s",
						"False\n");
				fclose(f);
			}
		} else if (strcmp(command, "clear") == 0) {
			command = strtok(command, "\n");
			clear(hash);
		} else if (strcmp(command, "print_bucket") == 0) {
			tok[1] = strtok(NULL, " ");
			tok[2] = strtok(NULL, "\n ");
			/*
			 * Verificam daca indexul
			 * bucket-ului este numar
			 */
			for (i = 0; i < strlen(tok[1]) - 1; i++) {
				if (!((tok[1][i] >= 48) &&
					(tok[1][i] <= 57))) {
					aux = 1;
					break;
				}
			}
			if (aux == 0) {
				index = atoi(tok[1]);
				if (index <= (*hash)->size) {
					list_p = (*hash)->bucket[index];
					/*
					 * daca avem doi parametri,
					 * printam la consola
					 */
					if (tok[2] == NULL) {
						print_bucket(&list_p);
						printf("\n");
					} else if (tok[2] != NULL) {
						/*
						 * avem 3 parametri
						 * -> scriem in fisier
						 */
						f = fopen(tok[2], "a");
						print_bf(&list_p, f);
						fprintf(f, "\n");
						fclose(f);
					}
				}
			}
		} else if ((strcmp(command, "print") == 0) ||
			strcmp(command, "print\n") == 0) {
			tok[1] = strtok(NULL, "\n ");
			/*
			 * un singur parametru,
			 * afisam in consola
			 */
			if (tok[1] == NULL) {
				print_hash(hash);
				printf("\n");
			/*
			 * doi parametri,
			 * -> scriem in fisier
			 */
			} else {
				f = fopen(tok[1], "a");
				print_hash_file(hash, f);
				fclose(f);
			}
		} else if (strcmp(command, "resize") == 0) {
			tok[1] = strtok(NULL, "\n ");
			if (strcmp(tok[1], "double") == 0) {
				new_s = 2 * (*hash)->size;
				*hash = resize(hash, new_s);
			} else if (strcmp(tok[1], "halve") == 0) {
				/* daca dimensiunea este impara */
				if ((*hash)->size % 2 == 1)
					new_s = ((*hash)->size - 1) / 2;
				else
					new_s = (*hash)->size / 2;
				*hash = resize(hash, new_s);
			}
		} else {
			perror("Invalid command!");
			exit(-1);
		}
	}
}
