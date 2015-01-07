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
    NoeudABR * tmp = rechercher_noeud(arbre, mot), *tmp2;

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
        tmp2=tmp;
        if (strcmp(tmp->mot, mot) > 0)
            tmp = tmp->filsGauche;
        else
            tmp = tmp->filsDroit;
    }
    if (strcmp(tmp2->mot, mot) > 0)
        tmp2->filsGauche = noeud;
    else
        tmp2->filsDroit = noeud;
    arbre->nb_mots_differents++;
    arbre->nb_mots_total++;
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
    int l=strlen(mot), i;
    noeud->mot = malloc(sizeof(char)*l);
    for (i=0 ; i<l ; i++)
        noeud->mot[i] = mot[i];
    mot[i]='\0';
    ajouter_position(&noeud->positions, ligne, ordre, num_phrase);
    noeud->filsDroit = NULL;
    noeud->filsGauche = NULL;
    return noeud;
}

void afficher_arbre (ArbreBR arbre){
    parcours_infixe(arbre.racine);
    printf("\n\n");
}

void parcours_infixe (NoeudABR * noeud){
    if (noeud != NULL){
        parcours_infixe(noeud->filsGauche);
        printf("- %s\n", noeud->mot);
        parcours_infixe(noeud->filsDroit);
    }
}

void afficher_phrase (ArbreBR * arbre, int num_phrase){


}

int rechercher_phrase (ArbreBR * arbre, char * mot1, char * mot2, int * resultat_phrase){
    NoeudABR *tmp1, *tmp2;
    int i = 0;
    tmp1 = rechercher_noeud(arbre, mot1);
    tmp2 = rechercher_noeud(arbre, mot2);
    if ((tmp1 == NULL) || (tmp2 == NULL))
        return -1;
    Position *pos1, *pos2;
    pos1 = tmp1->positions.debut;
    pos2 = tmp2->positions.debut;
    while ((pos1 != NULL) && (pos2 != NULL)){
        if (pos1->numero_phrase == pos2->numero_phrase){
            resultat_phrase[i] = pos1->numero_phrase;
            i++;
            pos1 = pos1->suivant;
            pos2 = pos2->suivant;
        }
        else if (pos1->numero_phrase < pos2->numero_phrase)
            pos1 = pos1->suivant;
        else
            pos2 = pos2->suivant;
    }
    return i-1;
}

