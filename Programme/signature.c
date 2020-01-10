#include "utils.h"
#include "rsa.h"
#include "sha256.h"

/** Fonction de signature d'un message. Renvoie la taille du message signé.
 * La sortie doit faire 36 blocs de plus que l'entrée
   Arguments:
   		entree: Tableau d'uint8_t, le message à signer.
   		tailleEntree: Taille du tableau
   		sortie: Tableau d'uint 8, le message signé.
   		rk: Clé rsa pour signer le message
*/
int signatureRsa(uint8_t* entree, int tailleEntree, uint8_t* sortie, struct rsaKey* rk){
    //On crée la signature du message
    uint32_t *hashTab = malloc(sizeof(uint32_t) * 8);
    sha256(entree, tailleEntree, hashTab);

    //On convertit en 9 blocs
    uint32_t *hashTab9Blocs = malloc(sizeof(uint32_t) * 9);
    changeFormat(hashTab, hashTab9Blocs);

    //On crypte le message
    uint32_t *hashTab9Encrypt = malloc(sizeof(uint32_t) * 9);
    decipherMessage(rk, hashTab9Blocs, 9, hashTab9Encrypt);

    //Convertit le hash en uint8
    uint8_t *hashEncrypt8bits = malloc(sizeof(uint8_t) * 9*4);
    int taillehash8 = convert32to8(hashTab9Encrypt, 9, hashEncrypt8bits);

    //On remplit la sortie
    for(int i = 0; i<tailleEntree; i++){
        sortie[i] = entree[i];
    }
    for(int i = 0; i<taillehash8; i++){
        sortie[tailleEntree+i] = hashEncrypt8bits[i];
    }

    return tailleEntree + 36;
}
/**Fonction qui renvoie 0 si le message est mal signé, 1 sinon.
 *      Arguments:
 *          entree:Tableau d'uint8, le message signé
 *          tailleEntree: Taille du tableau
 *          rk: Clé publique de l'expéditeur
 */
char verificationSignature(uint8_t* entree,int tailleEntree, struct rsaKey* rk){
    //On sépare le message et le sha
    uint8_t *message = malloc(sizeof(uint8_t)*(tailleEntree - 36));
    uint8_t *sha = malloc(sizeof(uint8_t)*(36));
    int j = 0;
    for(int i = 0; i<tailleEntree; i++){//On s'occupe du message
        if(i<tailleEntree -36){
            message[i] = entree[i];
        }
        if(i>= tailleEntree-36){
            sha[j] = entree[i];
            j = j+1;
        }
    }




    //On convertit sha 8bit en sha32bit.
    uint32_t* sha32 = malloc(sizeof(uint32_t)*9);
    int a = convert8to32(sha, 9*8, sha32);
    //On le décrypte
    uint32_t* sha32Decrypt = malloc(sizeof(uint32_t)*9);
    encryptionMessage(rk, sha32, 9, sha32Decrypt);

    //On calcule le sha du message
    uint32_t *hashTab = malloc(sizeof(uint32_t) * 8);
    sha256(message, tailleEntree-36, hashTab);

    //On calcule le sha du message 9 blocs
    uint32_t *hashTab9 = malloc(sizeof(uint32_t) * 9);
    changeFormat(hashTab, hashTab9);


    //On compare
    int i = 0;
    char identique = 1;
    while(i<9 && identique != 0){



        if(sha32Decrypt[i] != hashTab9[i]){
            identique = 0;
        }
        i = i +1;
    }
    return identique;

}
