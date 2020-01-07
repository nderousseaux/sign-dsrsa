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

off_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1;
}

int main(int argc, char** argv) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s fichierATester module exposantPublic\n", argv[0]);
        return EXIT_FAILURE;
    }

    uint32_t tailleFichier = fsize(argv[1]);


    uint8_t *tabFichier = malloc(sizeof(uint8_t)*tailleFichier);

    int fdIn=open(argv[1],O_RDONLY);
    int n=0;
    char buf[1];
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
    char resultat = verificationSignature(tabFichier, tailleFichier, &rk);

    if(resultat == 0){
        printf("La signature n'est pas valide ! \n");
    }
    else{
        printf("La signature est valide ! \n");
    }
}