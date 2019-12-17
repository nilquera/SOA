all: servidor client

servidor: servidor.c socketMng.o
	gcc -o servidor -g servidor.c socketMng.o

client: client.c socketMng.o
	gcc -o client -g client.c socketMng.o

socketMng.o: socketMng.c
	gcc -c -g socketMng.c

clean: 
	rm -f servidor client socketMng.o
