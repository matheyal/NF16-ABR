#include "liste.h"
#include "arbre.h"
#include "outils.h"

ArbreBR *creer_abr()
{
    /*On crée un nouvel arbre*/
    ArbreBR* abr=(ArbreBR*)malloc(sizeof(ArbreBR));
    /*Puisque l'arbre est vide, on affecte aux champ nb_mots_differents et nb_mots_total, et on affecte donc NULL
    à l'adresse de début de l'arbre*/
    abr->nb_mots_differents=0;
    abr->nb_mots_total=0;
    abr->racine=NULL;
    /*On retourne l'adresse de la nouvelle arbre*/
    return abr;
}

int ajouter_noeud(ArbreBR *arbre, NoeudABR *noeud)
{
    /*Cas où les pointeurs ne contiennent pas d'adresse*/
    if(arbre==NULL) return 0;
    if(noeud==NULL) return 0;
    /*On pointe sur la racine*/
    NoeudABR* x=arbre->racine;
    /*Si l'arbre est vide*/
    if (x==NULL)
    {
            /*Alors le noeud devient la raçine*/
            arbre->racine=noeud;
            /*On incrémente le nombre de noeuds*/
            arbre->nb_mots_differents++;
            /*L'insertion a reussi, on renvoit un code de retour positif*/
            return 1;
    }
    /*Sinon, on applique l'algorithme du cours*/
    /*On crée un pointeur*/
    NoeudABR* y=NULL;
    while(x!=NULL)
    {
        /*Tant que x est différent de NULL, on affecte à y l'adresse de x puis on parcourt l'arbre avec x*/
        y=x;
        /*Si le mot du noeud que l'on veut insérer se trouve avant le mot de celui est pointé par x dans le dictionnaire (Majuscules non prises en
        en compte) on va à gauche*/
        if (my_strcmp(noeud->mot,x->mot)<0)
        {
            x=x->filsGauche;
        }
        /*Si le mot du noeud que l'on veut insérer se trouve après le mot de celui est pointé par x dans le dictionnaire (Majuscules non prises en
        en compte) on va à droite*/
        else if (my_strcmp(noeud->mot,x->mot)>0)
        {
            x=x->filsDroit;
        }
        /*Sinon, les mots sont identiques, on insére sa position dans la liste des positions du noeud en spécifiant correctement les arguments
        de la fonction d'ajout de positions*/
        else
        {
            ajouter_position(
                &x->positions,
                noeud->positions.debut->numero_ligne,
                noeud->positions.debut->ordre,
                noeud->positions.debut->numero_phrase
            );
            /*On libére l'espace mémoire utilisée par le noeud*/
            free(noeud->mot);
            free(noeud->positions.debut);
            free(noeud);
            /*Dans ce cas on a insérer seulement une nouvelle position dans le noeud, on peut renvoyer un code de retour positif*/
            return 1;
        }
    }
    /*Maintenant, y pointe sur le père du noeud que l'on veut insérer : on insére soit à droite soit à gauche du noeud selon l'ordre du mot
    par rapport à celui contenu dans le mot dans le dictionnaire*/
    if (my_strcmp(noeud->mot,y->mot)<0)
    {
        /*Si il se trouve avant, on insére à gauche, et on incrémente le nombre de noeuds*/
        y->filsGauche=noeud;
        arbre->nb_mots_differents++;
        /*L'insertion du noeud s'est bien passée, on renvoit un code de retour positif*/
        return 1;
    }
    else
    {
        /*Sinon, on insére à droite, et on incrémente le nombre de noeuds*/
        y->filsDroit=noeud;
        arbre->nb_mots_differents++;
        /*L'insertion du noeud s'est bien passée, on renvoit un code de retour positif*/
        return 1;
    }
    /*Si aucun cas a été traité, il y a un problème d'ajout, on renvoit un code d'erreur 0*/
    return 0;
}

int charger_fichier(ArbreBR *arbre, char *filename)
{
    /*Pour manipuler le fichier, on utilise les fonctions d'entrée-sortie de haut niveau*/
    FILE* f=NULL;
    /*On déclare un flot de type FILE* qui sera initialisé à NULL*/
    if( (f = fopen(filename, "r"))==NULL)
    {
        /*Si l'ouverture du fichier a échoué, on renvoie un code d'erreur négatif*/
        perror("Impossible d'ouvrir le fichier !\n");
        return -1;
    }
    /*Sinon on définit les variables permettant de récupérer les mots du fichiers ainsi que leur position*/
    /*Le mot sera stocké dans la variable mot pouvant contenir 100 caractères*/
    char* mot = (char*) malloc(sizeof(char)*100);
    /*ptr pointe sur le premier élément de mot et va remplir au fur et à mesure le tableau de caractère mot*/
    char* ptr = &mot[0];
    /*c va prendre les caractères du fichiers*/
    char c;
    /*On initialise toutes les champs de position à 1 et le nombre de mots lus à 0*/
    int ordre = 1, ligne = 1, num_phrase = 1, nb_mots_lus = 0;
    //int point;
    /*Tant que qu'il y a pas d'erreurs d'entrée-sortie sur le flot f et que l'on a pas atteint la fin du fichier*/
    while (!ferror(f)&&!feof(f))
    {
        /*On lit le caractère sur le flot et on avance le curseur d'un caractère*/
        c=fgetc(f);
        switch (c)
        {
            /*Si on a récupéré un retour chariot alors on modifie la position pour le prochain mot */
            case '\n':  ligne +=1;
                        ordre = 1;
                        break;
            /*Si on a récupéré un . on marque la fin du mot et on ajoute le mot, on incrémente le nombre de mots lus et le numéro de phrase pour
            le prochain mot. On remet le pointeur au début du mot*/
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
            /*Si on a récupéré un espace, on marque la fin du mot et on augmente l'ordre pour le prochain mot */
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
            /*Sinon par défaut on récupére le caractère dans la case du mot pointé par ptr et on incrémente ptr*/
            default:    *ptr = c;
                        ptr+=1;
                        break;
        }
    }
    /*Après avoir fini de traiter tous les mots du fichier, on ferme le flot et on libère l'espace alloué par mot */
    fclose(f);
    free(mot);
    /*On retourne le nombre de mots lus*/
    return nb_mots_lus;
}

NoeudABR* rechercher_noeud(ArbreBR *arbre, char *mot)
{
    /*Si l'arbre n'existe pas, on renvoit NULL (erreur)*/
    if (arbre==NULL) return NULL;
    /*Sinon on récupère l'adresse de la racine dans ptr*/
    NoeudABR* ptr=arbre->racine;
    /*Tant que ptr est différent de NULL et que l'on n'a pas trouvé le mot souhaité*/
    while (ptr!=NULL && my_strcmp(mot,ptr->mot)!=0)
    {
        /*On se déplace à gauche ou à droite suivant la position lexicographique du mot par rapport à celui du noeud courrant*/
        if (my_strcmp(mot,ptr->mot)<0) ptr=ptr->filsGauche;
        else ptr=ptr->filsDroit;
    }
    /*Renvoie NULL si il n'y a eu aucune concordance, ou l'adresse du noeud contenant le mot recherché*/
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


