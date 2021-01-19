all: client server

client: client.o
	gcc -o client client.o

client.o: client.c client.h
	gcc -c client.c

server: server.o
	gcc -o server server.o

server.o: server.c server.h
	gcc -c server.c

clean:
	rm *.o
