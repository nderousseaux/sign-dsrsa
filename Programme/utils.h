#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
char *concatenate_param(int argc, char **argv, int nbShift);//Concatene les paramères
uint32_t getbitvalue(uint32_t v, uint32_t idx) ;//Renvoie la valeur d'un bit
uint8_t getbitvalue8(uint8_t v, uint8_t idx);
void printbits_32(uint32_t v); //Fonction pour afficher les blocs de 32bits
void printbits_8(uint8_t v); //Fonction pour afficher les blocs de 8bits
int convert32to8(uint32_t* entree, int taille, uint8_t* sortie); //Fonction qui convertit un tableau de uint32_t en tableau de uint8, renvoie la taille de la sortie
int convert8to32(uint8_t* in, uint8_t size, uint32_t* out);//Convertit tableau 8 bloc en tableau 32 blocs.