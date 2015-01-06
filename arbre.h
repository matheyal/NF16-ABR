#ifndef ARBRE_H_INCLUDED

#define ARBRE_H_INCLUDED

#include "liste.h"
#include "outils.h"

typedef struct noeudABR {
    char * mot;
    ListePosition positions;
    struct noeudABR *filsGauche;
    struct noeudABR *filsDroit;
}NoeudABR;

typedef struct arbreBR {
    NoeudABR * racine;
    int nb_mots_differents, nb_mots_total;
}ArbreBR;

ArbreBR * creer_ABR();
int ajouter_mot (ArbreBR * arbre, char * mot, int ligne, int ordre, int num_phrase);
NoeudABR * rechercher_noeud (ArbreBR * arbre, char * mot);
NoeudABR * creer_noeud (char * mot, int ligne, int ordre, int num_phrase);
int charger_fichier (ArbreBR * arbre, char * filename);
void afficher_arbre (ArbreBR arbre);
void parcours_infixe (NoeudABR * noeud);

#endif // ARBRE_H_INCLUDED
