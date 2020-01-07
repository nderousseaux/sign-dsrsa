all: testSha256 testSignature clean

sha256.o: sha256.h sha256.c
	gcc -c sha256.c

rsa.o: rsa.h rsa.c
	gcc -c rsa.c

utils.o: utils.h utils.c
	gcc -c utils.c

signature.o: sha256.o rsa.o signature.h signature.c
	gcc -c signature.c

testSha256: sha256.o utils.o testSha256.c
	gcc -o testSha256 -Wall sha256.o utils.o testSha256.c

testSignature: signature.o rsa.o sha256.o utils.o testSignature.c
	gcc -o testSignature -Wall signature.o rsa.o sha256.o utils.o testSignature.c

clean:
	rm *.o
