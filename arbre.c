#include "liste.h"
#include "arbre.h"
#include "outils.h"

ArbreBR *creer_abr()
{
    /*On cr�e un nouvel arbre*/
    ArbreBR* abr=(ArbreBR*)malloc(sizeof(ArbreBR));
    /*Puisque l'arbre est vide, on affecte aux champ nb_mots_differents et nb_mots_total, et on affecte donc NULL
    � l'adresse de d�but de l'arbre*/
    abr->nb_mots_differents=0;
    abr->nb_mots_total=0;
    abr->racine=NULL;
    /*On retourne l'adresse de la nouvelle arbre*/
    return abr;
}

int ajouter_noeud(ArbreBR *arbre, NoeudABR *noeud)
{
    /*Cas o� les pointeurs ne contiennent pas d'adresse*/
    if(arbre==NULL) return 0;
    if(noeud==NULL) return 0;
    /*On pointe sur la racine*/
    NoeudABR* x=arbre->racine;
    /*Si l'arbre est vide*/
    if (x==NULL)
    {
            /*Alors le noeud devient la ra�ine*/
            arbre->racine=noeud;
            /*On incr�mente le nombre de noeuds*/
            arbre->nb_mots_differents++;
            /*L'insertion a reussi, on renvoit un code de retour positif*/
            return 1;
    }
    /*Sinon, on applique l'algorithme du cours*/
    /*On cr�e un pointeur*/
    NoeudABR* y=NULL;
    while(x!=NULL)
    {
        /*Tant que x est diff�rent de NULL, on affecte � y l'adresse de x puis on parcourt l'arbre avec x*/
        y=x;
        /*Si le mot du noeud que l'on veut ins�rer se trouve avant le mot de celui est point� par x dans le dictionnaire (Majuscules non prises en
        en compte) on va � gauche*/
        if (my_strcmp(noeud->mot,x->mot)<0)
        {
            x=x->filsGauche;
        }
        /*Si le mot du noeud que l'on veut ins�rer se trouve apr�s le mot de celui est point� par x dans le dictionnaire (Majuscules non prises en
        en compte) on va � droite*/
        else if (my_strcmp(noeud->mot,x->mot)>0)
        {
            x=x->filsDroit;
        }
        /*Sinon, les mots sont identiques, on ins�re sa position dans la liste des positions du noeud en sp�cifiant correctement les arguments
        de la fonction d'ajout de positions*/
        else
        {
            ajouter_position(
                &x->positions,
                noeud->positions.debut->numero_ligne,
                noeud->positions.debut->ordre,
                noeud->positions.debut->numero_phrase
            );
            /*On lib�re l'espace m�moire utilis�e par le noeud*/
            free(noeud->mot);
            free(noeud->positions.debut);
            free(noeud);
            /*Dans ce cas on a ins�rer seulement une nouvelle position dans le noeud, on peut renvoyer un code de retour positif*/
            return 1;
        }
    }
    /*Maintenant, y pointe sur le p�re du noeud que l'on veut ins�rer : on ins�re soit � droite soit � gauche du noeud selon l'ordre du mot
    par rapport � celui contenu dans le mot dans le dictionnaire*/
    if (my_strcmp(noeud->mot,y->mot)<0)
    {
        /*Si il se trouve avant, on ins�re � gauche, et on incr�mente le nombre de noeuds*/
        y->filsGauche=noeud;
        arbre->nb_mots_differents++;
        /*L'insertion du noeud s'est bien pass�e, on renvoit un code de retour positif*/
        return 1;
    }
    else
    {
        /*Sinon, on ins�re � droite, et on incr�mente le nombre de noeuds*/
        y->filsDroit=noeud;
        arbre->nb_mots_differents++;
        /*L'insertion du noeud s'est bien pass�e, on renvoit un code de retour positif*/
        return 1;
    }
    /*Si aucun cas a �t� trait�, il y a un probl�me d'ajout, on renvoit un code d'erreur 0*/
    return 0;
}

int charger_fichier(ArbreBR *arbre, char *filename)
{
    /*Pour manipuler le fichier, on utilise les fonctions d'entr�e-sortie de haut niveau*/
    FILE* f=NULL;
    /*On d�clare un flot de type FILE* qui sera initialis� � NULL*/
    if( (f = fopen(filename, "r"))==NULL)
    {
        /*Si l'ouverture du fichier a �chou�, on renvoie un code d'erreur n�gatif*/
        perror("Impossible d'ouvrir le fichier !\n");
        return -1;
    }
    /*Sinon on d�finit les variables permettant de r�cup�rer les mots du fichiers ainsi que leur position*/
    /*Le mot sera stock� dans la variable mot pouvant contenir 100 caract�res*/
    char* mot = (char*) malloc(sizeof(char)*100);
    /*ptr pointe sur le premier �l�ment de mot et va remplir au fur et � mesure le tableau de caract�re mot*/
    char* ptr = &mot[0];
    /*c va prendre les caract�res du fichiers*/
    char c;
    /*On initialise toutes les champs de position � 1 et le nombre de mots lus � 0*/
    int ordre = 1, ligne = 1, num_phrase = 1, nb_mots_lus = 0;
    //int point;
    /*Tant que qu'il y a pas d'erreurs d'entr�e-sortie sur le flot f et que l'on a pas atteint la fin du fichier*/
    while (!ferror(f)&&!feof(f))
    {
        /*On lit le caract�re sur le flot et on avance le curseur d'un caract�re*/
        c=fgetc(f);
        switch (c)
        {
            /*Si on a r�cup�r� un retour chariot alors on modifie la position pour le prochain mot */
            case '\n':  ligne +=1;
                        ordre = 1;
                        break;
            /*Si on a r�cup�r� un . on marque la fin du mot et on ajoute le mot, on incr�mente le nombre de mots lus et le num�ro de phrase pour
            le prochain mot. On remet le pointeur au d�but du mot*/
            case '.':
            case '?':
            case '!':   *ptr = '\0';
                        if(ajouter_mot(arbre, strcpy((char*)malloc(sizeof(char) *sizeof(mot)), mot), ligne, ordre, num_phrase))
                        {
                            //point=1;
                            nb_mots_lus++;
                            num_phrase += 1;
                            ptr = &mot[0];
                        }
                        break;
            /*Si on a r�cup�r� un espace, on marque la fin du mot et on augmente l'ordre pour le prochain mot */
            case ',':
            case ';':
            case ':':
            case ' ':   *ptr = '\0';
                        if(ajouter_mot(arbre, mot, ligne, ordre, num_phrase))
                        {
                            nb_mots_lus++;
                            ordre ++;
                            ptr = &mot[0];
                        }
                        break;
            /*Sinon par d�faut on r�cup�re le caract�re dans la case du mot point� par ptr et on incr�mente ptr*/
            default:    *ptr = c;
                        ptr+=1;
                        break;
        }
    }
    /*Apr�s avoir fini de traiter tous les mots du fichier, on ferme le flot et on lib�re l'espace allou� par mot */
    fclose(f);
    free(mot);
    /*On retourne le nombre de mots lus*/
    return nb_mots_lus;
}

NoeudABR* rechercher_noeud(ArbreBR *arbre, char *mot)
{
    /*Si l'arbre n'existe pas, on renvoit NULL (erreur)*/
    if (arbre==NULL) return NULL;
    /*Sinon on r�cup�re l'adresse de la racine dans ptr*/
    NoeudABR* ptr=arbre->racine;
    /*Tant que ptr est diff�rent de NULL et que l'on n'a pas trouv� le mot souhait�*/
    while (ptr!=NULL && my_strcmp(mot,ptr->mot)!=0)
    {
        /*On se d�place � gauche ou � droite suivant la position lexicographique du mot par rapport � celui du noeud courrant*/
        if (my_strcmp(mot,ptr->mot)<0) ptr=ptr->filsGauche;
        else ptr=ptr->filsDroit;
    }
    /*Renvoie NULL si il n'y a eu aucune concordance, ou l'adresse du noeud contenant le mot recherch�*/
    return ptr;
}

void afficher_arbre(ArbreBR arbre)
{
    /*SI l'arbre est vide, on renvoit un message d'erreur*/
    if (arbre.racine==NULL) printf("Arbre vide !\n");
    else
        /*Sinon on affiche tout les noeuds depuis la racine de l'arbre*/
        afficher_noeud(arbre.racine);
}


