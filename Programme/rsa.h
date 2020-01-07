
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


struct rsa_key{
    uint64_t n;
    uint64_t e;
    uint64_t d;
};

uint32_t to_power(uint32_t a, uint32_t b,uint32_t mod);

uint32_t encryption_bloc(struct rsa_key* rk, uint32_t* part_message);
void encryption_message(struct rsa_key* rk, uint32_t* message, int taille_message, uint32_t* resultat);

uint32_t decipher_bloc(struct rsa_key* rk, uint32_t* part_message);
void decipher_message(struct rsa_key* rk, uint32_t* message, int taille_message, uint32_t* resultat);
