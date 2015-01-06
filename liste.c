#include "liste.h"

ListePosition *creer_liste_positions() {
    ListePosition * listeP = (ListePosition*) malloc(sizeof(ListePosition));
    listeP->debut = NULL;
    listeP->nb_elements = 0;

    return listeP;
}

Position * creer_position(int ligne, int ordre, int num_phrase) {
    Position * pos = (Position*) malloc(sizeof(Position));
    pos->numero_ligne = ligne;
    pos->ordre = ordre;
    pos->numero_phrase = num_phrase;
    pos->suivant = NULL;
    return pos;
}

int ajouter_position (ListePosition * listeP, int ligne, int ordre, int num_phrase) {
    Position * pos = creer_position(ligne, ordre, num_phrase);
    Position * tmp = listeP->debut;

    //Liste vide
    if (tmp == NULL) {
        listeP->debut = pos;
        //pos->suivant est déjà défini à NULL dans la fonction creer_position()
        return 1;
    }

    //Liste non-vide
    if ((tmp->numero_ligne > ligne) || ((tmp->numero_ligne == ligne) && (tmp->ordre > ordre))) {
        pos->suivant = tmp;
        listeP->debut = pos;
        return 1;
    }

    while ((tmp->suivant != NULL) && (tmp->suivant->numero_ligne < ligne)){
        tmp = tmp->suivant;
    }

    if ((tmp->suivant == NULL) || (tmp->suivant->numero_ligne > ligne)) {
        //Le mot à insérer est entre deux lignes déjà présentes dans la liste
        pos->suivant = tmp->suivant;
        tmp->suivant = pos;
        return 1;
    }

    //tmp->suivant->numero_ligne == ligne : Il y a déjà un mot sur la même ligne
    while ((tmp->suivant != NULL) && (tmp->suivant->numero_ligne == ligne) && (tmp->suivant->ordre < ordre)) {
        tmp = tmp->suivant;
    }
    if ((tmp->suivant != NULL) && (tmp->suivant->numero_ligne == ligne) && (tmp->suivant->ordre == ordre)) {
        //Le mot à l'endroit passé en paramètre est déjà dans la liste
        return 0;
    }
    /*On est soit :
        - à la fin de la liste
        - à la fin de la ligne
        - entre 2 mots de la ligne, à l'endroit où le nouveau mot doit être inséré
    */
    pos->suivant = tmp->suivant;
    tmp->suivant = pos;
    return 1;

}

