#include <stdint.h>
#include <stdio.h>
uint32_t get_bit_value(uint32_t v, uint32_t idx) ;//Renvoie la valeur d'un bit
uint8_t get_bit_value_8(uint8_t v, uint8_t idx);
void print_bits_32(uint32_t v); //Fonction pour afficher les blocs de 32bits
void print_bits_8(uint8_t v); //Fonction pour afficher les blocs de 8bits
int convert_32_to_8(uint32_t* entree, int taille, uint8_t* sortie); //Fonction qui convertit un tableau de uint32_t en tableau de uint8, renvoie la taille de la sortie
