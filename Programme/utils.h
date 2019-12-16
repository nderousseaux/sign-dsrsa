#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <math.h>
struct private_key{
	uint32_t p;
	uint32_t q;
	uint32_t d;
};

struct public_key{
	uint32_t n;
	uint32_t e;
};
void encryptionMessage(struct public_Key, const char *fileIn, char *fileOut);
void encryptionBloc(struct public_Key, uint8_t *partMessage, fileOut);
uint32_t decipher(struct private_key* pk, uint32_t crypted_message);
uint32_t toPower(uint32_t a, uint32_t b,uint32_t mod);

