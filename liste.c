#include "liste.h"

ListePosition* creer_liste_positions()
{
    /*On crée une nouvelle liste de positions */
    ListePosition* lp=(ListePosition*)malloc(sizeof(ListePosition));
    /*La liste est pour l'instant vide : on affecte donc NULL à l'adresse de début de liste */
    lp->debut=NULL;
    /*On affecte la valeur 0 au nombre d'éléments dans la nouvelle liste*/
    lp->nb_elements=0;
    /*on retoune la nouvelle liste, ie le pointeur sur la nouvelle liste*/
    return lp;
}

int ajouter_position(ListePosition* listeP, int ligne, int ordre, int num_phrase)
{
    /*On crée une nouvelle position*/
    Position* p=(Position*)malloc(sizeof(Position));
    /*On affecte à cette position ses champs entrés en argument de la fonction*/
    p->numero_ligne=ligne;
    p->numero_phrase=num_phrase;
    p->ordre=ordre;
     /*On initialise pour l'instant à NULL l'adresse de l'élément suivant la position*/
    p->suivant=NULL;
    /*Pour ordonner correctement la position d'un mot dans la liste, il faut savoir correctement où le placer. On a en première priorité la ligne
    où le mot se trouve, puis enfin l'ordre de la ligne auquelle il se trouve */

    /*Si la liste est vide OU la première position de la liste a sa ligne qui est strictement supérieure à celle de la nouvelle position du mot
    que l'on veut insérer OU la première position de la liste a sa ligne qui est égale à celle de la nouvelle position du mot MAIS mais l'ordre de
    cette dernière est (strictement) inférieure à celle de la première position de la liste */
    if  ((listeP->debut==NULL)||
         (listeP->debut->numero_ligne > ligne )||
         ((listeP->debut->numero_ligne==ligne)&&(listeP->debut->ordre > ordre)))
    {
        /*Dans ce cas, on fait une simple insertion en début de liste chainée*/
        p->suivant=listeP->debut;
        listeP->debut=p;
        /*On incrémente le nombre de positions dans la liste*/
        listeP->nb_elements++;
        /*L'implémentation de la nouvelle position dans la liste a reussi : on peut renvoyer un code de retour positif*/
        return 1;
    }
    else
    {
        /*Si nous ne sommes pas dans les conditions d'ajout en tête de liste, il faut placer la nouvelle position en fonction de sa ligne tout
        d'abord puis enfin selon son ordre */
        Position* ptr=listeP->debut;
       /*On crée un nouveau pointeur qui pointe en début de liste et tant qu'on n'est pas en fin de liste et que le numéro de ligne de la
        nouvelle position est strictement infénieure à celle de la position suivante celle courante pointée par ptr, alors on parcourt la
        liste en avançant d'un cran (Type d'insertion classique dans une liste triée, vue en cours)*/
        while((ptr->suivant!=NULL)&&(ptr->suivant->numero_ligne < ligne))
        {
            ptr=ptr->suivant;
        }
        /*On refait la même chose mais en raisonnant sur l'ordre de la position, en faisant attention de s'arrêter que cas où on dépasse l'ensemble
        des positions contenant la même ligne*/
        while((ptr->suivant!=NULL)&&(ptr->suivant->ordre < ordre)&&(ptr->suivant->numero_ligne==ligne))
        {
            ptr=ptr->suivant;
        }
        /*A ce stade, ptr pointe sur la position du mot qui se trouve juste avant notre nouvelle position, on insére à la suite de cette position*/
        p->suivant=ptr->suivant;
        ptr->suivant=p;
        /*On incrémente le nombre de positions dans la liste*/
        listeP->nb_elements++;
        /*On renvoit un code de retour positif pour spécifier que l'ajout s'est bien déroulé*/
        return 1;
    }
    /*Si l'ajout s'est mal passé, on renvoit le code erreur 0*/
    return 0;
}
