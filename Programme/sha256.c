#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//On définit les opérations utiles pour le sha256
#define Ch(x, y, z) ((x & y) ^ (~x & z))
#define Maj(x, y, z)    ((x & y) ^ (x & z) ^ (y & z))
#define ROTR(x, n)  ((x >> n) | (x << (32 - n)))
#define SHR(x, n)   (x >> n)
#define S0(x)       (ROTR(x, 2) ^ ROTR(x, 13) ^ ROTR(x, 22))
#define S1(x)       (ROTR(x, 6) ^ ROTR(x, 11) ^ ROTR(x, 25))
#define s0(x)       (ROTR(x, 7) ^ ROTR(x, 18) ^ SHR(x, 3))
#define s1(x)       (ROTR(x, 17) ^ ROTR(x, 19) ^ SHR(x, 10))

//On définit les constantes
#define un 0x100000000

//Valeurs initiales de hash
static const uint32_t depart[8] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

//Valeurs de K
static const uint32_t tableauK[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
        0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
        0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
        0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
        0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
        0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
        0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
        0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
        0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};


//On définit les structures
/**
 * Cette structure permettra de stocker les blocs de 512 bits sous forme d'un tableau de 16 blocs de 32 bits.
 * Utile dans la fonction sha256.
 */
struct bloc512{
    uint32_t mots[16];
};

/**
 * Fonction renvoyant le nombre de blocs de 512 bits nécessaires pour accueillir un message.
 *      Arguments :
 *          size: Taille en octet
 */
uint nbblocs(int size){


    //Le nombre de blocs est égal à 1 + tailleMessage/512 (division entière)
    int reste = 1 + size/512;

    if(size%512>=448){
        //S'il reste plus de 447 bits dans le dernier bloc, on ajoute un nouveau bloc
        reste+=1;
    }

    reste = reste*64;
    return reste;
}


/**
 * Fonction qui prépare un message au hashage. Renvoie la taille du message preparé (multiple de 64).
 *      Arguments :
 *          entree: Tableau d'uint8_t, le message à préparer.
 *          tailleEntree: Nombre de case du tableau.
 *          sortie: Tableau d'uint8_t, le message préparé.
 */
int bourrage(uint8_t* entree, int tailleEntree, uint8_t* sortie){
    //on obtient alors un message complété dont la longueur est supérieure de 512 bits au plus petit multiple de 512 bits supérieur à la longueur initiale du message.

    //On remplit le début de la table par le message
    int i;
    for(i = 0; i < tailleEntree; i++){
        sortie[i] = entree[i]; // On remplit le tab temp des bits du message
    }
    sortie[i] = 128; // On met un 1 après le message

    tailleEntree = tailleEntree*8;

    //On rajoute la taille du message à la fin de la table.
    sortie[nbblocs(tailleEntree)-1] = tailleEntree%256;//Dernier bloc
    sortie[nbblocs(tailleEntree)-2] = (tailleEntree-sortie[nbblocs(tailleEntree)-1])/256;
    sortie[nbblocs(tailleEntree)-3] = (tailleEntree-sortie[nbblocs(tailleEntree)-2])/256/256;
    sortie[nbblocs(tailleEntree)-4] = (tailleEntree-sortie[nbblocs(tailleEntree)-3])/256/256/256;
    sortie[nbblocs(tailleEntree)-5] = (tailleEntree-sortie[nbblocs(tailleEntree)-4])/256/256/256/256;
    sortie[nbblocs(tailleEntree)-6] = (tailleEntree-sortie[nbblocs(tailleEntree)-5])/256/256/256/256/256;
    sortie[nbblocs(tailleEntree)-7] = (tailleEntree-sortie[nbblocs(tailleEntree)-6])/256/256/256/256/256/256;
    sortie[nbblocs(tailleEntree)-8] = (tailleEntree-sortie[nbblocs(tailleEntree)-7])/256/256/256/256/256/256/256;

    return nbblocs(tailleEntree);
}


/**
 * Découpage du message en n mots de 512 bits. Renvoie le nombre de mots
 *      Arguments :
 *          entree: Tableau d'uint8_t, le message à découper.
 *          tailleEntree: Nombre de case du tableau.
 *          sortie: Tableau de bloc512, le message découpé.
 */
int decoupage(uint8_t* entree, int tailleEntree, struct bloc512* sortie){

    int nbBloc512 = tailleEntree/64;

    for(int i = 0; i<nbBloc512; i++){ //On parcourt les blocs de 512 bits
        for(int j = 0; j<64; j= j+4){ //On parcourt les 16 blocs de 32 bits.
            //On crée le bloc de 32 que l'on veut mettre
            uint32_t bloc = 0;
            int indexBloc = i*64 + j;
            bloc = entree[indexBloc];
            bloc = bloc << 8;
            indexBloc++;
            bloc = bloc + entree[indexBloc];
            bloc = bloc << 8;
            indexBloc++;
            bloc = bloc + entree[indexBloc];
            bloc = bloc << 8;
            indexBloc++;
            bloc = bloc + entree[indexBloc];
            sortie[i].mots[j/4] = bloc;
        }
    }

    return nbBloc512;
}

/**
 * Hahshage du message découpé.
 *      Arguments :
 *          entree: Tableau de bloc512, le message préparé, puis découpé.
 *          nbBloc512: Nombre de case du tableau.
 *          sortie: Tableau de 8 uint_t32, le message hashé.
 */
void hash(struct bloc512* messageDecoupe, int nbBloc512, uint32_t* hashTab){
    //On initialise les valeurs initiales
    memcpy(hashTab, &depart, 32);
    uint32_t w[64];
    uint32_t a;
    uint32_t b;
    uint32_t c;
    uint32_t d;
    uint32_t e;
    uint32_t f;
    uint32_t g;
    uint32_t h;
    uint32_t t1 = 0;
    uint32_t t2 = 0;

    for(int i=0; i<nbBloc512; i++){
        //On met à jour les valeurs intermédiaires
        a = hashTab[0];
        b = hashTab[1];
        c = hashTab[2];
        d = hashTab[3];
        e = hashTab[4];
        f = hashTab[5];
        g = hashTab[6];
        h = hashTab[7];

        //On crée le sha256
        //Pour t allant de 0 à 63
        for(int t=0; t<64; t++){
            if(t<=15){
                w[t] = messageDecoupe[i].mots[t];
            }
            else{
                w[t] = s1(w[t-2]) + w[t-7] + s0(w[t-15]) + w[t-16];
            }

            t1 = h + S1(e) + Ch(e,f,g) + tableauK[t] + w[t];
            t2 = S0(a) +  Maj(a,b,c);
            h=g;
            g=f;
            f=e;
            e=d+t1;
            d=c;
            c=b;
            b=a;
            a = t1+t2;
        }

        hashTab[0] = a+hashTab[0];
        hashTab[1] = b+hashTab[1];
        hashTab[2] = c+hashTab[2];
        hashTab[3] = d+hashTab[3];
        hashTab[4] = e+hashTab[4];
        hashTab[5] = f+hashTab[5];
        hashTab[6] = g+hashTab[6];
        hashTab[7] = h+hashTab[7];

    }

}

/**
 * Fonction qui calcule le sha256 d'un message
 *      Arguments :
 *          message: Tableau d'uint8_t, le message à hasher
 *          taille: Nombre de case du tableau.
 *          hashTab: Tableau de 8 uint32_t, le message hashé.
 */
void sha256(uint8_t* message, int taille, uint32_t* hashTab){

    //Dabord, on bourre le message
    uint8_t* tabBourre;
    tabBourre = calloc(64, nbblocs(taille)); //On initilise un tableau de uint8 de la bonne taille
    int tailleBourrage = bourrage(message, taille, tabBourre);

    //Le message est découpé en nblocs de 512 bits
    struct bloc512 messageDecoupe[tailleBourrage/64];
    int nbBloc512 = decoupage(tabBourre, tailleBourrage, messageDecoupe);

    //On calcule le hash
    hash(messageDecoupe, nbBloc512, hashTab);


}

//Fonction qui calcule le sha256 d'un message
/**
 * Fonction qui affiche un sha256
 *      Arguments :
 *          sha256: Tableau de 8 uint32_t, le hash à afficher.
 */
void printSha256(uint32_t* sha256){
    for(int i = 0; i<8; i++){
        printf("%x", sha256[i]);
    }
    printf("\n");
}
/**
 * Fonction modifie un sha256 sur 8 blocs, en un sha256 sur 9blocs
 *      Arguments :
 *          entree: Tableau de 8 uint32_t, le hash à convertir.
 *          sortie: Tableau de 9 uint32_t, le hash convertit.
 */
void changeFormat(uint32_t* entree, uint32_t* sortie){
    for(int i = 0; i<8; i++){
        sortie[i] = entree[i];

        //On remplit le 9ème bloc
        //On prend les bits de poids fort du mot
        uint32_t maskFort = 0b11000000000000000000000000000000;
        uint32_t bitFort = entree[i]&maskFort;

        //Ensuite, on le décale plus ou moint en fonction de i.
        for(int j=0; j<i; j++){
            bitFort = bitFort>>2; //TODO: A vérifier
        }
        sortie[8] = sortie[8] + bitFort;
    }
}
