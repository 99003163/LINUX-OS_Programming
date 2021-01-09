all: p1 p2 p3

p1: p1.c p.h
	gcc -o p1.out p1.c -lrt

p2: p2.c p.h
	gcc -o p2.out p2.c -lrt

p3: p3.c p.h
	gcc -o p3.out p3.c -lrt

runp1:
	./p1.out

runp2:
	./p2.out

runp3:
	./p3.out

clean:
	rm -rf *.out *.o
