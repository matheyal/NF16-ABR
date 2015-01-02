#include "arbre.h"

ArbreBR * creer_ABR() {
    ArbreBR * arbre = (ArbreBR*) malloc(sizeof(ArbreBR));
    arbre->racine = NULL;
    arbre->nb_mots_differents = arbre->nb_mots_total = 0;
    return arbre;
}

int ajouter_mot (ArbreBR * arbre, char * mot, int ligne, int ordre, int num_phrase) {

    if (arbre->racine == NULL){ //Cas d'un arbre vide
        NoeudABR * noeud = creer_noeud(mot, ligne, ordre, num_phrase);
        arbre->racine = noeud;
        return 1;
    }

    //L'arbre est non vide
    format_str(mot);
    NoeudABR * tmp = rechercher_noeud(arbre, mot);

    if (tmp != NULL) {
        //Le mot est déjà présent dans l'arbre : on ajoute la nouvelle position
        ajouter_position(&tmp->positions, ligne, ordre, num_phrase);
        arbre->nb_mots_total++;
        return 1;
    }

    //Le mot n'est pas présent dans la liste : on crée un noeud et on l'insère dans l'arbre
    NoeudABR * noeud = creer_noeud(mot, ligne, ordre, num_phrase);
    tmp = arbre->racine;

    while(tmp != NULL) {
        if (strcmp(tmp->mot, mot) > 0)
            tmp = tmp->filsGauche;
        else
            tmp = tmp->filsDroit;
    }
    tmp = noeud;
    return 1;

}

NoeudABR * rechercher_noeud (ArbreBR * arbre, char * mot) {
    NoeudABR * tmp = arbre->racine;
    while ((tmp != NULL) && (strcmp(tmp->mot, mot) != 0)){
        if (strcmp(tmp->mot, mot) > 0)
            tmp = tmp->filsGauche;
        else
            tmp = tmp->filsDroit;
    }
    return tmp;
}

NoeudABR * creer_noeud (char * mot, int ligne, int ordre, int num_phrase) {
    NoeudABR * noeud = (NoeudABR*) malloc(sizeof(NoeudABR));
    noeud->mot = mot;
    ajouter_position(&noeud->positions, ligne, ordre, num_phrase);
    noeud->filsDroit = NULL;
    noeud->filsGauche = NULL;
    return noeud;
}
