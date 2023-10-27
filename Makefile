CC = gcc
CFLAGS = -Wall -Wextra

all: Server/server Client/client

server: Server/server.c
	$(CC) $(CFLAGS) -o server Server/server.c

client: Client/client.c
	$(CC) $(CFLAGS) -o client Client/client.c

clean:
	rm -f Server/server Client/client fifo*