all: Server Client

Server: server.c srvclnt.h
	gcc -o server.out server.c -lrt
	
Client: client.c srvclnt.h
	gcc -o client.out client.c -lrt
	
runClient:
	./client.out

runServer:
	./server.out

clean:
	rm -rf *.out *.o
