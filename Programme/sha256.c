#include "utils.h"

int main(int argc, char** argv) {

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s messageAHasher\n", argv[0]);
        return EXIT_FAILURE;
    }

    //On lance le sha
    uint32_t* hashTab = malloc(sizeof(uint32_t)*8);
    sha256((uint8_t*) argv[1], strlen(argv[1]), hashTab);