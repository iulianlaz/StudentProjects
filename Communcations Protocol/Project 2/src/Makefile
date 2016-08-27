CC = gcc
CCFLAGS = -Wall


build:
	$(CC)  -o client client.c
	$(CC)  -o server selectserver.c

.PHONY : clean
clean:
	rm -f client server client.o server.o
 
