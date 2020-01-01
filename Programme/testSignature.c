/**
 * Main de test pour les dernières question : signature rsa
 */
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>
#include "signature.h"

int main(int argc, char** argv) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s fichierATester module exposantPublic\n", argv[0]);
        return EXIT_FAILURE;
    }

    //On convertit le fichier en tableau de uint8_t
    int fdIn=open(argv[1],O_RDONLY);
    char buf[1];
    int n;
    int tailleFichier;
    //On lit tout le fichier pour connaitre sa taille
    while((n=read(fdIn,buf,1))){
        tailleFichier = tailleFichier + 1;
    }
    close(fdIn);

    uint8_t *tabFichier = malloc(sizeof(uint8_t)*tailleFichier);

    fdIn=open(argv[1],O_RDONLY);
    n=0;
    int i;
    while((n=read(fdIn,buf,1))){
        tabFichier[i] = buf[0];
        i = i+1;
    }

    close(fdIn);


    //On lance la vérification
    struct rsaKey rk;
    rk.e = atoi(argv[3]);
    rk.n = atoi(argv[2]);
    verificationSignature(tabFichier, tailleFichier, &rk);
}