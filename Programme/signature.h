#include "rsa.h"
#include "sha256.h"

int signatureRsa(uint8_t* entree, int tailleEntree, uint8_t* sortie, struct rsaKey* rk); // Fonction de signature d'un message. Renvoie la taille du message signé.
char verificationSignature(uint8_t* entree,int tailleEntree, struct rsaKey* rk); //Fonction qui renvoie 0 si le message est mal signé, 1 sinon.