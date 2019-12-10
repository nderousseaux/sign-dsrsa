#include <stdint.h>

struct private_key{
	uint32_t p;
	uint32_t q;
	uint32_t d;
};

struct public_key{
	uint32_t n;
	uint32_t e;
};

/* Fonction de déchiffrement d'un bloc de 32 bits
   Arguments:
   		pk: pointeur sur la clef privée, contenant les valeurs p, q, et l'inverse modulaire d de e, mod n
   		crypted_message: bloc de longueur 32 bits à déchiffrer
*/

uint32_t decipher(struct private_key* pk, uint32_t crypted_message){
	uint32_t p=pk->p;
	uint32_t q=pk->q;
	uint32_t d=pk->d;
	uint32_t n=p*q;
	uint32_t decryped_message=(crypted_message*d)%n;
	return decryped_message;

}