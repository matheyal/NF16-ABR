#include "liste.h"

ListePosition* creer_liste_positions()
{
    /*On cr�e une nouvelle liste de positions */
    ListePosition* lp=(ListePosition*)malloc(sizeof(ListePosition));
    /*La liste est pour l'instant vide : on affecte donc NULL � l'adresse de d�but de liste */
    lp->debut=NULL;
    /*On affecte la valeur 0 au nombre d'�l�ments dans la nouvelle liste*/
    lp->nb_elements=0;
    /*on retoune la nouvelle liste, ie le pointeur sur la nouvelle liste*/
    return lp;
}

int ajouter_position(ListePosition* listeP, int ligne, int ordre, int num_phrase)
{
    /*On cr�e une nouvelle position*/
    Position* p=(Position*)malloc(sizeof(Position));
    /*On affecte � cette position ses champs entr�s en argument de la fonction*/
    p->numero_ligne=ligne;
    p->numero_phrase=num_phrase;
    p->ordre=ordre;
     /*On initialise pour l'instant � NULL l'adresse de l'�l�ment suivant la position*/
    p->suivant=NULL;
    /*Pour ordonner correctement la position d'un mot dans la liste, il faut savoir correctement o� le placer. On a en premi�re priorit� la ligne
    o� le mot se trouve, puis enfin l'ordre de la ligne auquelle il se trouve */

    /*Si la liste est vide OU la premi�re position de la liste a sa ligne qui est strictement sup�rieure � celle de la nouvelle position du mot
    que l'on veut ins�rer OU la premi�re position de la liste a sa ligne qui est �gale � celle de la nouvelle position du mot MAIS mais l'ordre de
    cette derni�re est (strictement) inf�rieure � celle de la premi�re position de la liste */
    if  ((listeP->debut==NULL)||
         (listeP->debut->numero_ligne > ligne )||
         ((listeP->debut->numero_ligne==ligne)&&(listeP->debut->ordre > ordre)))
    {
        /*Dans ce cas, on fait une simple insertion en d�but de liste chain�e*/
        p->suivant=listeP->debut;
        listeP->debut=p;
        /*On incr�mente le nombre de positions dans la liste*/
        listeP->nb_elements++;
        /*L'impl�mentation de la nouvelle position dans la liste a reussi : on peut renvoyer un code de retour positif*/
        return 1;
    }
    else
    {
        /*Si nous ne sommes pas dans les conditions d'ajout en t�te de liste, il faut placer la nouvelle position en fonction de sa ligne tout
        d'abord puis enfin selon son ordre */
        Position* ptr=listeP->debut;
       /*On cr�e un nouveau pointeur qui pointe en d�but de liste et tant qu'on n'est pas en fin de liste et que le num�ro de ligne de la
        nouvelle position est strictement inf�nieure � celle de la position suivante celle courante point�e par ptr, alors on parcourt la
        liste en avan�ant d'un cran (Type d'insertion classique dans une liste tri�e, vue en cours)*/
        while((ptr->suivant!=NULL)&&(ptr->suivant->numero_ligne < ligne))
        {
            ptr=ptr->suivant;
        }
        /*On refait la m�me chose mais en raisonnant sur l'ordre de la position, en faisant attention de s'arr�ter que cas o� on d�passe l'ensemble
        des positions contenant la m�me ligne*/
        while((ptr->suivant!=NULL)&&(ptr->suivant->ordre < ordre)&&(ptr->suivant->numero_ligne==ligne))
        {
            ptr=ptr->suivant;
        }
        /*A ce stade, ptr pointe sur la position du mot qui se trouve juste avant notre nouvelle position, on ins�re � la suite de cette position*/
        p->suivant=ptr->suivant;
        ptr->suivant=p;
        /*On incr�mente le nombre de positions dans la liste*/
        listeP->nb_elements++;
        /*On renvoit un code de retour positif pour sp�cifier que l'ajout s'est bien d�roul�*/
        return 1;
    }
    /*Si l'ajout s'est mal pass�, on renvoit le code erreur 0*/
    return 0;
}
