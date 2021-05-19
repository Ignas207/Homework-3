CFLAGS = -Wall -Wextra -Wconversion 
CC = gcc

all: main
		$(CC) $(CFLAGS) -o generator.out gen_main.o -lssl -lcrypto

main:
		$(CC) -c $(CFLAGS) -o gen_main.o generator.c
