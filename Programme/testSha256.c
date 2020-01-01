/**
 * Main de test pour la question 1 : sha256
 */

#include "sha256.h"

int main(int argc, char** argv) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s messageAHasher\nEntrez le message sans espaces ! \n", argv[0]);
        return EXIT_FAILURE;
    }

    //On lance le sha
    uint32_t *hashTab = malloc(sizeof(uint32_t) * 8);
    sha256((uint8_t *) argv[1], strlen(argv[1]), hashTab);

    //On affiche le sha
    printSha256(hashTab);
    for(int i = 0; i<8; i++){
        printbits_32(hashTab[i]);
        printf("\n");
    }

    printf("\n\n Sha convertit en 9 blocs :\n");
    //On convertit le sha en 9 blocs
    uint32_t *hashTab9 = malloc(sizeof(uint32_t) * 9);
    changeFormat(hashTab, hashTab9);
    for(int i = 0; i<9; i++){
        printbits_32(hashTab9[i]);
        printf("\n");
    }
}