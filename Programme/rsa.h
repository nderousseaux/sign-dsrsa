
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


struct rsaKey{
    uint64_t n;
    uint64_t e;
    uint64_t d;
};

uint32_t toPower(uint32_t a, uint32_t b,uint32_t mod);

uint32_t encryptionBloc(struct rsaKey* rk, uint32_t* partMessage);
void encryptionMessage(struct rsaKey* rk, uint32_t* message, int tailleMessage, uint32_t* resultat);

uint32_t decipherBloc(struct rsaKey* rk, uint32_t* partMessage);
void decipherMessage(struct rsaKey* rk, uint32_t* message, int tailleMessage, uint32_t* resultat);
