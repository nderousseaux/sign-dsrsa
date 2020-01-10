/**
 * Main de test pour la question 1 : sha256
 */
#include "utils.h"
#include "sha256.h"

int main(int argc, char** argv) {

    //Message à hasher
    if (argc < 2) {
        fprintf(stderr, "Usage: %s Message A Hasher \n", argv[0]);
        return EXIT_FAILURE;
    }


    //On concatène le message.
    char *str = concatenate_param(argc, argv, 1);


    //On lance le sha
    uint32_t *hashTab = malloc(sizeof(uint32_t) * 8);
    sha256((uint8_t *) str, strlen(str), hashTab);

    //On affiche le sha
    printf("On affiche le sha en 8 bits :\n");
    printSha256(hashTab);

    //On convertit le sha
    uint32_t *hashTab9 = malloc(sizeof(uint32_t)*9);
    changeFormat(hashTab, hashTab9);

    //On affiche le sha9
    printf("\n\nOn affiche le sha en 9 bits :\n");
    printSha256_9(hashTab9);

    for(int i = 0; i<9; i++){
        printbits_32(hashTab9[i]);
        printf("\n");
    }

    free(str);
    free(hashTab);
    free(hashTab9);
}
