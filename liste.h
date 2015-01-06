#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct position {
    int numero_ligne, ordre, numero_phrase;
    struct position * suivant;
} Position;

typedef struct listePosition {
    Position * debut;
    int nb_elements;
} ListePosition;

ListePosition *creer_liste_positions();
int ajouter_position (ListePosition * listeP, int ligne, int ordre, int num_phrase);
Position * creer_position(int ligne, int ordre, int num_phrase);

#endif // LISTE_H_INCLUDED
