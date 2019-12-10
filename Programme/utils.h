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

uint32_t decipher(struct private_key* pk, uint32_t crypted_message);
