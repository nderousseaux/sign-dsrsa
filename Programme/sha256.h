#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//On définit les opérations utiles pour le sha256
#define Ch(x, y, z)
#define Maj(x, y, z)
#define ROTR(x, n)
#define SHR(x, n)
#define S0(x)
#define S1(x)
#define s0(x)
#define s1(x)

//On définit les constantes
#define un

//Valeurs initiales de hash
static const uint32_t depart[8];

//Valeurs de K
static const uint32_t tableauK[64];

//On définit les structures
//Cette structure permettra de stocker les blocs de 512 bits sous forme d'un tableau de 16 blocs de 32 bits
struct bloc512;



//On définit les fonctions
uint nbblocs(int size); //Nombre de bloc de 256 pour acceillir le message
int bourrage(uint8_t* entree, int tailleEntree, uint8_t* sortie); //Bourage du message
int decoupage(uint8_t* entree, int tailleEntree, struct bloc512* sortie); //Découpage du message en n mots de 512 bits
void hash(struct bloc512* messageDecoupe, int nbBloc512, uint32_t* hashTab); //Hashage du message découpé
void sha256(uint8_t* message, int taille, uint32_t* hashTab); //Fonction qui calcule le sha256 d'un message
void printSha256(uint32_t* sha256); //Affiche le sha256 en hexadecimal
void changeFormat(uint32_t* entree, uint32_t* sortie); //Modifie un sha256 sur 8 blocs, en un sha256 sur 9blocs
void printSha256_9(uint32_t* sha256); //Affiche le sha256 en hexadecimal 9 blocs
