/**
 * Main de test pour la question 1 : sha256
 */
#include "utils.h"
#include "sha256.h"

int main(int argc, char** argv) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s messageAHasher\nEntrez le message sans espaces ! \n", argv[0]);
        return EXIT_FAILURE;
    }

    //On lance le sha
    uint32_t *hash_tab = malloc(sizeof(uint32_t) * 8);
    sha256((uint8_t *) argv[1], strlen(argv[1]), hash_tab);

    //On affiche le sha
    print_sha256(hash_tab);
    for(int i = 0; i<8; i++){
        print_bits_32(hash_tab[i]);
        printf("\n");
    }

    printf("\n\n Sha convertit en 9 blocs :\n");
    //On convertit le sha en 9 blocs
    uint32_t *hash_tab9 = malloc(sizeof(uint32_t) * 9);
    change_format(hash_tab, hash_tab9);
    for(int i = 0; i<9; i++){
        print_bits_32(hash_tab9[i]);
        printf("\n");
    }
}
