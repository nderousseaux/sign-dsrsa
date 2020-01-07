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
int signature_rsa(uint8_t* entree, int taille_entree, uint8_t* sortie, struct rsa_key* rk){
    //On crée la signature du message
    uint32_t *hash_tab = malloc(sizeof(uint32_t) * 8);
    sha256(entree, taille_entree, hash_tab);

    //On convertit en 9 blocs
    uint32_t *hash_tab_9Blocs = malloc(sizeof(uint32_t) * 9);
    change_format(hash_tab, hash_tab_9Blocs);

    //On crypte le message
    uint32_t *hash_tab_9Encrypt = malloc(sizeof(uint32_t) * 9);
    decipher_message(rk, hash_tab_9Blocs, 9, hash_tab_9Encrypt);

    //Convertit le hash en uint8
    uint8_t *hash_encrypt_8bits = malloc(sizeof(uint8_t) * 9*4);
    int taille_hash8 = convert_32_to_8(hash_tab_9Encrypt, 9, hash_encrypt_8bits);

    //On remplit la sortie
    for(int i = 0; i<taille_entree; i++){
        sortie[i] = entree[i];
    }
    for(int i = 0; i<taille_hash8; i++){
        sortie[taille_entree+i] = hash_encrypt_8bits[i];
    }

    return taille_entree + 36;
}
/**Fonction qui renvoie 0 si le message est mal signé, 1 sinon.
 *      Arguments:
 *          entree:Tableau d'uint8, le message signé
 *          taille_entree: Taille du tableau
 *          rk: Clé publique de l'expéditeur
 */
char verification_signature(uint8_t* entree,int taille_entree, struct rsa_key* rk){
    //On sépare le message et le sha
    uint8_t *message = malloc(sizeof(uint8_t)*(taille_entree - 36));
    uint8_t *sha = malloc(sizeof(uint8_t)*(36));
    int j = 0;
    for(int i = 0; i<taille_entree; i++){//On s'occupe du message
        if(i<taille_entree -36){
            message[i] = entree[i];
        }
        if(i>= taille_entree-36){
            sha[j] = entree[i];
            j = j+1;
        }
    }




    //On convertit sha 8bit en sha32bit.
    uint32_t* sha32 = malloc(sizeof(uint32_t)*9);
    for(int i = 0; i<9; i++){
        sha32[i] =  (sha[(i*4)+0] << 24) + (sha[(i*4)+1] << 16) + (sha[(i*4)+2] << 8) + sha[(i*4)+3];
    }

    //On le décrypte
    uint32_t* sha32_decrypt = malloc(sizeof(uint32_t)*9);
    encryption_message(rk, sha32, 9, sha32_decrypt);

    //On calcule le sha du message
    uint32_t *hash_tab = malloc(sizeof(uint32_t) * 8);
    sha256(message, taille_entree-36, hash_tab);

    //On compare
    int i = 0;
    char identique = 1;
    while(i<8 && identique != 0){
        if(sha32_decrypt[i]<<2 != hash_tab[i]<<2){
            identique = 0;
        }
        i = i +1;
    }
    return identique;

}
