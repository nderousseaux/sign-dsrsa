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

off_t fsize(const char *file_name) {
    struct stat st;

    if (stat(file_name, &st) == 0)
        return st.st_size;

    return -1;
}

int main(int argc, char** argv) {

    if (argc != 4) {
        fprintf(stderr, "Usage: %s fichierATester module exposantPublic\n", argv[0]);
        return EXIT_FAILURE;
    }

    uint32_t taille_fichier = fsize(argv[1]);


    uint8_t *tab_fichier = malloc(sizeof(uint8_t)*taille_fichier);

    int fd_in=open(argv[1],O_RDONLY);
    int n=0;
    char buf[1];
    int i;
    while((n=read(fd_in,buf,1))){
        tab_fichier[i] = buf[0];
        i = i+1;
    }

    close(fd_in);


    //On lance la vérification
    struct rsa_key rk;
    rk.e = atoi(argv[3]);
    rk.n = atoi(argv[2]);
    char resultat = verification_signature(tab_fichier, taille_fichier, &rk);

    if(resultat == 0){
        printf("La signature n'est pas valide ! \n");
    }
    else{
        printf("La signature est valide ! \n");
    }
}