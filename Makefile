CFLAGS = -g3 -Wall -Wextra -Wconversion 
CC = gcc

all: main func reading insertNode
		$(CC) $(CFLAGS) -o homework3 main.o func.o f_reading.o f_insertNode.o
		rm main.o func.o f_reading.o f_insertNode.o

main:
		$(CC) -c $(CFLAGS) -o main.o hmwrk_main.c

reading:
		$(CC) -c $(CFLAGS) -o f_reading.o ./Functions/Reading/reading.c

insertNode:
		$(CC) -c $(CFLAGS) -o f_insertNode.o ./Functions/InsertNode/InsertNode.c

func:
		$(CC) -c $(CFLAGS) -o func.o hmwrk_func.c
