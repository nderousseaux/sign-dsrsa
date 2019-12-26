/*
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
*/
#include "utils.h"

int main(){
	public_key pub_key;

	pub_key.n=2773;
	pub_key.e=17;

	private_key priv_key;

	priv_key.p=47;
	priv_key.q=59;
	priv_key.d=157;


	return 0;
}


    //On affiche le sha
    printSha256(hashTab);

    return 0;
}