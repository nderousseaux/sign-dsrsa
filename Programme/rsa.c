#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>

#include <math.h>


struct rsa_key{
    uint64_t n;
    uint64_t e;
    uint64_t d;
};



//TODO:Doc sur cette fonction
uint32_t to_power(uint32_t a, uint32_t b, uint32_t mod){
    uint64_t res=a;
    for(int i=1; i<b; i++){
        res = (res*a)%mod;
    }
    return (uint32_t )res;

}

/** Fonction de chiffrement d'un bloc de 32 bits
   Arguments:
   		rk: pointeur sur la clef publique, contenant les valeurs n, e
   		part_message: bloc de longueur 32 bits à chiffrer
*/
uint32_t encryption_bloc(struct rsa_key* rk, uint32_t part_message){

    uint32_t e = rk->e;
    uint32_t n = rk->n;
    return to_power(part_message, e, n);
}

/** Fonction de chiffrement d'un message
*   Arguments:
*   		rk: pointeur sur la clef public, contenant les valeurs n, e
*   		message : Tableau d'uint32_t à chiffrer.
*   		taille_message : Nombre de case du tableau
 *   		resultat : Message chiffré avec la clé publique
*/
void encryption_message(struct rsa_key* rk, uint32_t* message, int taille_message, uint32_t* resultat) {
    for (int i = 0; i < taille_message; i++) {
        resultat[i] = encryption_bloc(rk, message[i]);
    }
}

/** Fonction de déchiffrement d'un bloc de 32 bits
   Arguments:
   		rk: pointeur sur la clef privée, contenant les valeurs p, q et d
   		partMessage: bloc de longueur 32 bits à déchiffrer
*/
uint32_t decipher_bloc(struct rsa_key* rk, uint32_t part_message){
    uint32_t d = rk->d;
    uint32_t n = rk->n;
    return to_power(part_message, d, n);
}

/** Fonction de dechiffrement d'un message
*   Arguments:
*   		rk: pointeur sur la clef privée, contenant les valeurs p, d et d
*   		message : Tableau d'uint32_t à déchiffrer.
*   		tailleMessage : Nombre de case du tableau
 *   		resultat : Message déchiffré.
*/
void decipher_message(struct rsa_key* rk, uint32_t* message, int taille_message, uint32_t* resultat){
    for (int i = 0; i < taille_message; i++) {
        resultat[i] = decipher_bloc(rk, message[i]);
    }
}
