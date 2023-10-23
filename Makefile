CC=gcc

all: client server 

shell:  ./client.c ./server.c
	$(CC) $^ -o bin/$@ 	
	
clean:
	- rm 

.PHONY: all  clean