#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * Fonction qui convertit un tableau de uint32_t en tableau de uint8, renvoie la taille de la sortie
 *      Arguments:
 *          entree:Tableau d'uint32_t à convertir
 *          taille:Taille du tableau
 *          sortie: Tableau d'uint8_t, l'entrée convertie (4 fois plus grand que l'entrée).
*/
int convert32to8(uint32_t* entree, int taille, uint8_t* sortie){
    for(int i = 0; i<taille; i++){
        sortie[i*4] = entree[i]>>24;
        sortie[(i*4)+1] = entree[i]>>16;
        sortie[(i*4)+2] = entree[i]>>8;
        sortie[(i*4)+3] = entree[i];
    }

    return taille*4;
}

/**
 * Fonction qui concatene des arguments en une seule chaine
 *      Arguments:
 *          argc: Nombre d'arguments
 *          argv: Tableau des arguments
 *          nbShift : Index de l'argument de départ
 */
char *concatenate_param(int argc, char **argv, int nbShift){
    int     i;
    int     length;

    length = argc;
    for (i = nbShift; i < argc; ++i)
    {
        length += strlen(argv[i]);
    }

    char    *str;
    if((str = malloc(sizeof(char) * (length + 1))) == NULL)
    {
        return (0);
    }

    str[0] = 0;
    for (i = nbShift; i < argc; ++i)
    {
        strcat(str, argv[i]);
        strcat(str, " ");
    }
    str[length] = '\0';

    return (str);
}

/**
 * Conversion d'un tableau de bloc de 8 bits en tableau de bloc 32bits renvoie la taille de la sortie
 *      Arguments :
 *          in: Tableau en entrée
 *          size: Taille de l'entrée
 *          out: Tableau de sortie
 */
 int convert8to32(uint8_t* in, uint8_t size, uint32_t* out){
    int size32 = (int)size/8;
    for(size_t i = 0; i<size32; i++){
        out[i] =  (in[(i*4)+0] << 24) + (in[(i*4)+1] << 16) + (in[(i*4)+2] << 8) + in[(i*4)+3];
    }
    return size32;
 }

//Fonction pour afficher la valeur d'un bit
uint32_t getbitvalue(uint32_t v, uint32_t idx)
{
    return (v >> idx) & 1;
}
//Fonction pour afficher la valeur d'un bit
uint8_t getbitvalue8(uint8_t v, uint8_t idx)
{
    return (v >> idx) & 1;
}
//Fonction pour afficher les blocs de 32bits
void printbits_32(uint32_t v)
{
    for (uint32_t i = 32; i > 0; --i){
        if(i%8 == 0){
            printf(" ");
        }
        printf("%u", getbitvalue(v, i-1));

    }
}
//Fonction pour afficher les blocs de 8bits
void printbits_8(uint8_t v){
    for (uint8_t i = 8; i > 0; --i){
        if(i%8 == 0){
            printf(" ");
        }
        printf("%u", getbitvalue8(v, i-1));

    }
}
