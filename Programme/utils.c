#include <stdint.h>
#include <stdio.h>
/**
 * Fonction qui convertit un tableau de uint32_t en tableau de uint8, renvoie la taille de la sortie
 *      Arguments:
 *          entree:Tableau d'uint32_t à convertir
 *          taille:Taille du tableau
 *          sortie: Tableau d'uint8_t, l'entrée convertie (4 fois plus grand que l'entrée).
*/
int convert_32_to_8(uint32_t* entree, int taille, uint8_t* sortie){
    for(int i = 0; i<taille; i++){
        sortie[i*4] = entree[i]>>24;
        sortie[(i*4)+1] = entree[i]>>16;
        sortie[(i*4)+2] = entree[i]>>8;
        sortie[(i*4)+3] = entree[i];
    }

    return taille*4;
}

//Fonction pour afficher la valeur d'un bit
uint32_t get_bit_value(uint32_t v, uint32_t idx)
{
    return (v >> idx) & 1;
}
//Fonction pour afficher la valeur d'un bit
uint8_t get_bit_value_8(uint8_t v, uint8_t idx)
{
    return (v >> idx) & 1;
}
//Fonction pour afficher les blocs de 32bits
void print_bits_32(uint32_t v)
{
    for (uint32_t i = 32; i > 0; --i){
        if(i%8 == 0){
            printf(" ");
        }
        printf("%u", get_bit_value(v, i-1));

    }
}
//Fonction pour afficher les blocs de 8bits
void print_bits_8(uint8_t v){
    for (uint8_t i = 8; i > 0; --i){
        if(i%8 == 0){
            printf(" ");
        }
        printf("%u", get_bit_value_8(v, i-1));

    }
}
