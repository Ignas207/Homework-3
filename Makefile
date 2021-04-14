CFLAGS = -Wall -Wextra -Wconversion 
CC = gcc

all: main func
		$(CC) $(CFLAGS) -o homework2 main.o func.o
		rm main.o func.o

main:
		$(CC) -c $(CFLAGS) -o main.o hmwrk_main.c

func:
		$(CC) -c $(CFLAGS) -o func.o hmwrk_func.c
