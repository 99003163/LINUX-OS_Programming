all: Server Client

Server: s1.c SC.h
	gcc -o s1.out s1.c -lrt
	
Client: c1.c SC.h
	gcc -o c1.out c1.c -lrt
	
runClient:
	./c1.out

runServer:
	./s1.out

clean:
	rm -rf *.out *.o
