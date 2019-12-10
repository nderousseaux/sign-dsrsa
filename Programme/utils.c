#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//Chiffrement d'un message 
void encryptionMessage(struct public_Key, const char *fileIn, char *fileOut){

	int fd = open(fileIn, O_RDONLY);
	char* buf[4];
	int nb = read(fd, buf, 4);

	while( nb >= 4){
		encryptionBloc(public_Key, buf, fileOut);
		int nb = read(fd, buf, 4);
	}
	encryptionBloc(public_Key, nb, fileOut);
}

//Chiffrement d'un bloc du fichier qui est ensuite renvoyé dans le fichier de sortie
void encryptionBloc(struct public_Key, uint8_t *partMessage, fileOut){

	partMessage = puissanceModulo(partMessage, public_Key.e, public_Key.n);
	write(fileOut, partMessage, 4);
}

//Calcul et retourne la puissance d'un valeur à un certain modulo
int moduloPuissance(int val, int puissance, int modulo){
	
	int res = 1;
	for( int i = 1; i <= puissance; i++){
		res = res * val;
		while( res > modulo){
			res -= modulo;
		}
	}
	return res;
}