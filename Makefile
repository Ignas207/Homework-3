CFLAGS = -g3 -Wall -Wextra -Wconversion 
CC = gcc

all: main func reading insertNode createNode printList findNode nodeSelect nodeEdit
		$(CC) $(CFLAGS) -o homework3 main.o func.o f_reading.o f_insertNode.o f_createNode.o f_printList.o f_findNode.o f_nodeSelect.o f_nodeEdit.o
		rm main.o func.o f_reading.o f_insertNode.o f_createNode.o f_printList.o f_findNode.o f_nodeSelect.o f_nodeEdit.o

main:
		$(CC) -c $(CFLAGS) -o main.o hmwrk_main.c

reading:
		$(CC) -c $(CFLAGS) -o f_reading.o ./Functions/Reading/reading.c

insertNode:
		$(CC) -c $(CFLAGS) -o f_insertNode.o ./Functions/InsertNode/InsertNode.c

createNode:
		$(CC) -c $(CFLAGS) -o f_createNode.o ./Functions/CreateNode/createNode.c

printList:
		$(CC) -c $(CFLAGS) -o f_printList.o ./Functions/Printlist/printlist.c

findNode:
		$(CC) -c $(CFLAGS) -o f_findNode.o ./Functions/Searching/findNodebyKey.c

nodeSelect:
		$(CC) -c $(CFLAGS) -o f_nodeSelect.o ./Functions/NodeSelect\ and\ edit/nodeSelect.c

nodeEdit:
		$(CC) -c $(CFLAGS) -o f_nodeEdit.o ./Functions/NodeSelect\ and\ edit/nodeEdit.c

func:
		$(CC) -c $(CFLAGS) -o func.o hmwrk_func.c
