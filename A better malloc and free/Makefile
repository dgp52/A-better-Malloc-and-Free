CC = gcc
CFLAGS = -Wall -g -m32
RM = rm -rf

all: memgrind.c mymalloc.o
	$(CC) $(CFLAGS) -o memgrind memgrind.c mymalloc.o

mymalloc.o: mymalloc.c mymalloc.h
	$(CC) $(CFLAGS) -c mymalloc.c

clean: 
	rm -rf *.o