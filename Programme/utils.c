#include<stdint.h>

/*
* Fonction calculant la signature sha256 d'un message
* - message : param: message à hacher
* - signature : retour : signature du message(8bits)
* Code de retour : 0 en cas de succès, -1 en cas d'erreur
*/
int signature(uint8_t *message, uint8_t *signature){
  //On calcule le hashage du message
  uint8_t* message_hashe;
  hashage(*message, *message_hashe); //TODO:Créer la fonction de hashage

  //On calcule

  signature = hashage(message, )

}
