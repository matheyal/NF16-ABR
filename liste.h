#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define BUFSIZE 4000

/*Définition de la structure Position contenant le champ numero_ligne qui contient le numéro de ligne du mot, le champ ordre qui contient
l'ordre du mot dans la ligne, et le champ numero_phrase qui contient le numéro de phrase du mot*/
typedef struct Position
{
    int numero_ligne;
    int ordre;
    int numero_phrase;
    struct Position* suivant;
}Position;

/*Définition de la structure ListePosition qui contient le champ debut qui pointe sur le début de la liste de Position
et le champ nb_elements qui contient le nombre d'éléments de la liste*/
typedef struct ListePosition
{
    Position* debut;
    int nb_elements;
}ListePosition;

/*Déclaration des fonctions relatives à la gestion de la liste de positions*/
ListePosition* creer_liste_positions();
int ajouter_position(ListePosition* listeP, int ligne, int ordre, int num_phrase);

#endif // LISTE_H_INCLUDED
