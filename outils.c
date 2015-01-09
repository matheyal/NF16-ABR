#include "liste.h"
#include "arbre.h"
#include "outils.h"

NoeudABR* creer_noeud()
{
    NoeudABR* node=(NoeudABR*)malloc(sizeof(NoeudABR));
    node->filsDroit=NULL;
    node->filsGauche=NULL;
    ListePosition* x = creer_liste_positions();
    node->positions = *x;
    return node;
}

char* StringToLower(char* str)
{
    /*Convertit la chaîne de caractères str en minuscules*/
    int i=0;
    char* NewString=(char*)malloc(100*sizeof(char));
    strcpy(NewString,str);
    while(NewString[i]!='\0')
    {
        if (isupper(NewString[i])) NewString[i]=tolower(NewString[i]);
        i++;
    }
    return NewString;
}

int my_strcmp(char* str1,char* str2)
{
    return (  strcmp( StringToLower(str1) , StringToLower(str2) )  );
}

int ajouter_mot(ArbreBR *arbre, char* mot, int ligne, int ordre, int num_phrase)
{/*Ajoute un mot dans l'ABR (fait appel à ajouter_noeud() de arbre.c) */
    char* mot2;
    mot2 = StringToLower(mot);
    if (mot[0] == '\0') return 0;
    NoeudABR* n = creer_noeud();
    n->mot=mot2;
    ajouter_position(&(n->positions), ligne, ordre, num_phrase);
    arbre->nb_mots_total++;
    return ajouter_noeud(arbre, n);
}

void afficher_noeud(NoeudABR* x)
{ /*Affiche les caractéristiques de tous les noeuds de l'arbre grace à un parcours infixe de l'ABR*/
   if (x!=NULL)
   {
    afficher_noeud(x->filsGauche);
    printf("%s : %d occurences trouvee(s) !\n", x->mot, x->positions.nb_elements);
    afficher_noeud(x->filsDroit);
   }
}

int maxi(int a,int b)
{
    if (a<b) return b;
    return a;
}

int hauteur(NoeudABR* noeud)
{ /*Retourne la hauteur du noeud en parametre (hauteur de l'abre si noeud = racine)*/
    if (noeud==NULL) return -1;
    return 1+maxi(hauteur(noeud->filsGauche),hauteur(noeud->filsDroit));
}

int hauteur_arbre(ArbreBR* arbre)
{
    return hauteur(arbre->racine);
}

int abs(int a)
{ /*Retourne la valeur absolue de l'entier a*/
    if (a>=0) return a;
    return -a;
}

int equilibre_noeud(NoeudABR* noeud)
{ /*Calcule l'équilibre d'un noeud*/
    return (hauteur(noeud->filsDroit)-hauteur(noeud->filsGauche));
}

int est_equilibre(NoeudABR* noeud)
{
    if ((noeud==NULL) || (abs(equilibre_noeud(noeud))<=1) && (est_equilibre(noeud->filsGauche)) && (est_equilibre(noeud->filsDroit)) ) return 1;
    return 0;
}

void afficher_position(NoeudABR* noeud)
{ /*Afficher toutes les positions d'un mot (noeud)*/
    if (noeud==NULL) printf("Erreur : Saisie incorrecte !\n");
    else
    {
        Position* ptr=noeud->positions.debut;
        while(ptr!=NULL)
        {
            printf("Numero ligne : %d\nOrdre : %d\nNumero phrase : %d\n\n",ptr->numero_ligne,ptr->ordre,ptr->numero_phrase);
            ptr=ptr->suivant;
        }
        printf("%d occurences trouvee(s) !\n\n",noeud->positions.nb_elements);
    }
}

void afficher_fichier(char* filename)
{
    FILE* f=NULL;
    if( (f = fopen(filename, "r"))==NULL)
    {
        perror("Impossible d'ouvrir le fichier !\n");
    }
    char buffer[BUFSIZE];
    int compt_ligne=1;
    while(fgets(buffer, sizeof(buffer), f))
    {
        printf("\nLigne %d : %s",compt_ligne,buffer);
        compt_ligne++;
    }
    printf("\n\n");
    fclose(f);
}

void afficher_phrase_occurence(int num_phrase, char* filename)
{ /*Affiche une phrase (selon son numéro) à partir d'un fichier*/
    FILE* f=NULL;
    int c;

    if( (f = fopen(filename, "r"))==NULL)
    {
        perror("Impossible d'ouvrir le fichier !\n");
        exit(EXIT_FAILURE);
    }
    int j=1;
    while(j<num_phrase) //Parcours du fichier jusqu'à la phrase recherchee
    {
        c=fgetc(f);
        if (c=='.'/* || c=='?' || c=='!'*/) j++;
    }
    c=fgetc(f);
    while(c!='.' && c!=EOF) //Affiche la phrase recherchée (jusqu'au point suivant ou la fin du fichier)
    {
        putchar(c);
        c=fgetc(f);
    }
    rewind(f);
    printf(".\n\n");
}

void afficher_phrases(ArbreBR* arbre,char* mot1, char* mot2,char* filename)
{ /*Affiche toutes les phrases contenant les deux mots entrés en paramètres*/
    NoeudABR* x=rechercher_noeud(arbre,mot1); //x=NULL si le mot n'est pas trouvé
    NoeudABR* y=rechercher_noeud(arbre,mot2); //y=NULL si le mot n'est pas trouvé
    int trouve=0, compt=0;
    printf("Bonjour\n\n");
    if (x==NULL || y==NULL) printf("Erreur de saisie des 2 mots\n\n"); //Un des mots n'est pas dans le texte
    else
    {
        Position* ptr1= x->positions.debut;
        Position* ptr2= y->positions.debut;
        while ((ptr1 != NULL) && (ptr2 != NULL)){ /*On parcourt les liste de positions des deux mots à la recherche de phrases communes*/
            if (ptr1->numero_phrase == ptr2->numero_phrase){ //Ils apparaissent dans une même phrase
                trouve = 1;
                compt++;
                printf("Phrase : %d\n",ptr1->numero_phrase);
                afficher_phrase_occurence(ptr1->numero_phrase,filename); //Affiche la phrase entièrement
                ptr1 = ptr1->suivant;
                ptr2 = ptr2->suivant; //On passe aux positions suivantes des 2 noeuds
            }
            /*Quand la position d'un des 2 noeuds a un num_phrase inférieur à l'autre, on passe à sa position suivante*/
            else if (ptr1->numero_phrase < ptr2->numero_phrase)
                ptr1 = ptr1->suivant;
            else
                ptr2 = ptr2->suivant;
        }
    }
    if (!trouve) printf("Aucune occurence trouvee !\n\n");
    else printf("\n\n%d phrases trouvee(s) !\n",compt);
}

void free_arbre (ArbreBR * arbre, NoeudABR * noeud){
    /*Parcours postfixe de l'abre pour libérer tous les fils d'un noeud avant de le libérer lui-même
    (évite les erreurs d'accès)*/
    if (noeud != NULL){
        free_arbre(arbre, noeud->filsGauche);
        free_arbre(arbre, noeud->filsDroit);
        free_noeud(noeud);
    }
    free(arbre);
}

void free_noeud (NoeudABR * noeud){
    /*On libère toutes les positions de la liste des positions du noeud avant de libérer la liste puis le noeud*/
    Position * pos_tmp = noeud->positions.debut, *pos_tmp2;
    while (pos_tmp != NULL){
        pos_tmp2 = pos_tmp->suivant;
        free(pos_tmp);
        pos_tmp = pos_tmp2;
    }
    free(&(noeud->positions));
    free(noeud);
}
