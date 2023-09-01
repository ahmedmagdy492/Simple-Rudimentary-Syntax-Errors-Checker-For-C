CC=cc

all:
	$(CC) -c Stack.c -o Stack.o
	$(CC) -c main.c -o main.o
	$(CC) Stack.o main.o -o main
clear:
	rm -rf core.*
	rm -rf main.o
	rm -rf Stack.o
	rm -rf main
