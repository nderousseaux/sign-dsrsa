#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <unistd.h>

typedef
struct private_key{
	uint32_t p;
	uint32_t q;
	uint32_t d;
}
private_key;

typedef
struct public_key{
	uint32_t n;
	uint32_t e;
}
public_key;

uint32_t toPower(uint32_t a, uint32_t b, uint32_t mod){
	uint32_t res = a;
	for(int i=1; i<b;i++){
		res=res*a%mod;
	}
	return res;
}

/* Fonction de déchiffrement d'un bloc de 32 bits
   Arguments:
   		pk: pointeur sur la clef privée, contenant les valeurs p, q, et l'inverse modulaire d de e, mod n
   		crypted_message: bloc de longueur 32 bits à déchiffrer
*/

void decipher(private_key* pk, char* fileIn, char* fileOut){
    int fdIn=open(fileIn,O_RDONLY);
    int fdOut=open(fileOut,O_WRONLY);
    char buf[4];
    int n;
    while((n=read(fdIn,buf,4))){
        uint32_t decipheredBloc=decipherBloc(pk,buf);
        write(fdOut,&decipheredBloc,n);
    }
    close(fdOut);
    close(fdIn);
}

/* Fonction de déchiffrement d'un bloc de 32 bits
   Arguments:
   		pk: pointeur sur la clef public, contenant les valeurs n, e
   		partMessage: bloc de longueur 32 bits à déchiffrer
*/