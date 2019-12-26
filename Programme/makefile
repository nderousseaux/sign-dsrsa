all: main clean

rsa.o: rsa.h rsa.c
	gcc -c rsa.c

utils.o: utils.h utils.c
	gcc -c utils.c

main: utils.o rsa.o main.c 
	gcc -o main -Wall utils.o rsa.o main.c

sha256: utils.o sha256.c
    gcc -o sha256 -Wall utils.o sha256.c

clean:
	rm *.o