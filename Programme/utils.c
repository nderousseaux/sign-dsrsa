#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


struct private_key{
	uint32_t p;
	uint32_t q;
	uint32_t d;
};

struct public_key{
	uint32_t n;
	uint32_t e;
};

/* Fonction de déchiffrement d'un bloc de 32 bits
   Arguments:
   		pk: pointeur sur la clef privée, contenant les valeurs p, q, et l'inverse modulaire d de e, mod n
   		crypted_message: bloc de longueur 32 bits à déchiffrer
*/

uint32_t decipher(struct private_key* pk, uint32_t crypted_message){
	uint32_t p=pk->p;
	uint32_t q=pk->q;
	uint32_t d=pk->d;
	uint32_t n=p*q;
	uint32_t decryped_message=(crypted_message*d)%n;
	return decryped_message;
}

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