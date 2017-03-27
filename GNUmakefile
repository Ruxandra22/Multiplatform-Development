CC = gcc
CFLAGS = -Wall -Wextra -g -fPIC

LDFLAGS = -L.

.PHONY: build clean

build: tema1
	
tema1: main.o bucket.o hashtable.o parsecommand.o libhash.so
	$(CC) $(CFLAGS) main.o bucket.o hashtable.o parsecommand.o -o tema1 -lhash $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

bucket.o: bucket.c
	$(CC) $(CFLAGS) -c bucket.c

hashtable.o: hashtable.c
	$(CC) $(CFALGS) -c hashtable.c

parsecommand.o: parsecommand.c
	$(CC) $(CFLAGS) -c parsecommand.c
clean:
	rm -f *.o *~ tema1
