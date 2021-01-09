all: Server Client

Server: srvr.c srvclnt.h
	gcc -o srvr.out srvr.c -lrt
	
Client: clnt.c srvclient.h
	gcc -o clnt.out clnt.c -lrt
	
runClient:
	./clnt.out

runServer:
	./srvr.out

clean:
	rm -rf *.out *.o
