/*
 * Osman Maria - Ruxandra
 * Grupa 334CA
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bucket.h"
#include "hashtable.h"
#include "hash.h"
#include "parsecommand.h"

#define BUFFERSIZE 20000

int main(int argc, char *argv[])
{

	int size;
	char buffer[BUFFERSIZE];
	char *command_stdin;
	int i;
	FILE *fp;
	char *line;
	hashtable *hash;

	/* numar gresit de argumente date in linia de comanda */
	if (argc < 2) {
		perror("Arguments error!");
		return -1;
	}
	size = atoi(argv[1]);
	if (size <= 0) {
		perror("Bad size");
		exit(-1);
	}
	hash = create_hashtable(size);
	/* citesc de la stdin pentru ca lipsesc parametrii */
	if (argc == 2) {
		command_stdin = fgets(buffer, BUFFERSIZE, stdin);
		while ((command_stdin != NULL)) {
			parse_command(command_stdin, stdin, &hash);
			command_stdin = fgets(buffer, BUFFERSIZE, stdin);
		}
	}
	/* Daca am mai mult de 2 argumente, citesc din fisiere */
	if (argc > 2) {
		for (i = 2; i < argc; i++) {
			fp = fopen(argv[i], "r");
			while ((line = fgets(buffer, BUFFERSIZE, fp)) != NULL)
				parse_command(line, fp, &hash);
			fclose(fp);
		}
	}
	if (hash != NULL)
		destroy_hash(&hash);
	return 0;
}
