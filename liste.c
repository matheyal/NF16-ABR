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
        //pos->suivant est d�j� d�fini � NULL dans la fonction creer_position()
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
        //Le mot � ins�rer est entre deux lignes d�j� pr�sentes dans la liste
        pos->suivant = tmp->suivant;
        tmp->suivant = pos;
        return 1;
    }

    //tmp->suivant->numero_ligne == ligne : Il y a d�j� un mot sur la m�me ligne
    while ((tmp->suivant != NULL) && (tmp->suivant->numero_ligne == ligne) && (tmp->suivant->ordre < ordre)) {
        tmp = tmp->suivant;
    }
    if ((tmp->suivant != NULL) && (tmp->suivant->numero_ligne == ligne) && (tmp->suivant->ordre == ordre)) {
        //Le mot � l'endroit pass� en param�tre est d�j� dans la liste
        return 0;
    }
    /*On est soit :
        - � la fin de la liste
        - � la fin de la ligne
        - entre 2 mots de la ligne, � l'endroit o� le nouveau mot doit �tre ins�r�
    */
    pos->suivant = tmp->suivant;
    tmp->suivant = pos;
    return 1;

}

