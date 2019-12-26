#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <math.h>
typedef
struct{
	uint32_t p;
	uint32_t q;
	uint32_t d;
}private_key;

typedef
struct{
	uint32_t n;
	uint32_t e;
}public_key;

void decipher(private_key* pk, char* fileIn, char* fileOut);
uint32_t toPower(uint32_t a, uint32_t b,uint32_t mod);
uint32_t decipherBloc(private_key* pk, char* bloc);
uint32_t encryptionBloc(public_key* pk, uint32_t* partMessage);
void encryptionMessage(public_key* pk, const char *fileIn, char *fileOut);
