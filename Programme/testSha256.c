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
    printSha256(hashTab);

    free(str);
    free(hashTab);
}
