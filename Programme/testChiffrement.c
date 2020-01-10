/**
 * Main de test pour la question 3 : déchiffrement rsa
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "utils.h"
#include "rsa.h"


off_t fsize(const char *filename) {
    struct stat st;

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1;
}

int main(int argc, char** argv) {

    //Message à hasher
    if (argc < 2) {
        fprintf(stderr, "Usage: %s FichierIn Module Exposant", argv[0]);
        return EXIT_FAILURE;
    }

    uint32_t tailleFichier = fsize(argv[1]);

    struct rsaKey rk;
    rk.d = atoi(argv[3]);
    rk.n = atoi(argv[2]);

    uint32_t *tabFichier = malloc(sizeof(uint8_t)*tailleFichier);

    int fdIn=open(argv[1],O_RDONLY);
    uint32_t buf[1];
    int nb;
    int i = 0;
    while( (nb=read(fdIn,buf, sizeof(buf))) ){
        tabFichier[i] = buf[0];

    }

    close(fdIn);


    //On décrypte
    uint32_t *res = malloc(sizeof(uint32_t)*tailleFichier);
    decipherMessage(&rk, tabFichier, tailleFichier, res);

    for(int i = 0; i<tailleFichier; i++){
        printbits_32(res[i]);
        printf("\n");
    }
}
