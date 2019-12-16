#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>  
#include <math.h>
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

uint32_t decipherBloc(private_key* pk, char* bloc){
	uint32_t p=pk->p;
	uint32_t q=pk->q;
	uint32_t d=pk->d;
	uint32_t n=p*q;
	return toPower(*bloc,d,n);
}

/* Fonction de déchiffrement d'un fichier
   Arguments:
   		pk: pointeur sur la clef privée, contenant les valeurs p, q, et l'inverse modulaire d de e, mod n
   		crypted_message: fichier à déchiffrer
*/
void decipher(private_key* pk, char* fileIn, char* fileOut){
	int fdIn=open(fileIn,O_RDONLY);
	int fdOut=open(fileOut,O_WRONLY);
	uint8_t buf[4];
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

uint32_t encryptionBloc(public_key* pk, uint32_t* partMessage){

	uint32_t e = pk->e;
	uint32_t n = pk->n;
	return  toPower(*partMessage, e, n);
}

/* Fonction de déchiffrement d'un fichier
   Arguments:
   		pk: pointeur sur la clef public, contenant les valeurs n, e
   		*fileIn : fichier d'entrée à chiffré
   		*fileOut : fichier sortie représentant le fichier chiffré
*/

void encryptionMessage(public_key* pk, const char *fileIn, char *fileOut){

	int fdIn=open(fileIn,O_RDONLY);
	int fdOut=open(fileOut,O_WRONLY);
	uint32_t buf[4];
	int nb;
	while( (nb=read(fdIn,buf,4)) ){
		uint32_t cipheredBloc = encryptionBloc(pk, buf);
		write(fdOut,&cipheredBloc,nb);
	}
	close(fdOut);
	close(fdOut);
}
