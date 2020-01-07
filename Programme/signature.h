#include "rsa.h"
#include "sha256.h"

int signature_rsa(uint8_t* entree, int taille_entree, uint8_t* sortie, struct rsa_key* rk); // Fonction de signature d'un message. Renvoie la taille du message signé.
char verification_signature(uint8_t* entree,int taille_entree, struct rsa_key* rk); //Fonction qui renvoie 0 si le message est mal signé, 1 sinon.