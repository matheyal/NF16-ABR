#include "liste.h"
#include "arbre.h"
#include "outils.h"
//outil.c : pb main 6 : avec certains mot.
int main()
{
    printf("Bonjour !\n\n");
    /*Variables utilisées pour gérer le menu et les appels de fonction*/
    int choix, mots_lus, fichier_charge=0;
    char* filename=(char*)malloc(200*sizeof(char));
    char* filename2=(char*)malloc(200*sizeof(char));
    char* mot=(char*)malloc(50*sizeof(char));
    char* mot1=(char*)malloc(50*sizeof(char));
    char* mot2=(char*)malloc(50*sizeof(char));
    ArbreBR* a=NULL;

        /*Affichage de l'en-tete du programme */
    printf("\tBienvenue dans votre programme de classement alphabetique de texte\n\n");

    while(1)
    {
     printf("Menu principal : Veuillez choisir une fonction a effectuer \n");
        printf("\t1 - Creer un arbre binaire de recherche\n");
        printf("\t2 - Charger un fichier dans l'ABR\n");
        printf("\t3 - Afficher les caracteristiques de l'ABR\n");
        printf("\t4 - Afficher tous les mots distincts de l'ABR par ordre alphabetique\n");
        printf("\t5 - Rechercher un mot dans l'ABR\n");
        printf("\t6 - Afficher les phrases contenant les 2 mots saisis\n");
        printf("\t7 - Afficher un fichier ligne par ligne\n");
        printf("\t8 - Quitter le programme\n");
        scanf("%d", &choix);
        switch (choix)
        {
            /*Création ABR*/
            case 1:
                    a=creer_abr();
                    if (a!=NULL) printf("Arbre cree !\n\n");
                    else
                        printf("Erreur de création de l'arbre.\n\n");
                    break;

            /*Charger un fichier*/
            case 2:

                    if (a!=NULL)
                    {
                        printf("Veuillez saisir le fichier a charger en chemin relatif ou absolu : ");
                        scanf("%s",filename);
                        mots_lus=charger_fichier(a,filename);
                        if (mots_lus==-1) printf("Veuillez verifier votre saisie de chemin.\n\n");
                        else
                        {
                            fichier_charge=1;
                            if(mots_lus==0) printf("Aucun mot n'a pu etre lu !\n\n");
                            else
                                printf("%d mots ont ete lus dans le fichier !\n\n",mots_lus);
                        }
                    }
                    else
                        printf("Impossible ! Arbre non cree !\n\n");
                    break;

            /*Afficher caractériqtiques ABR*/
            case 3:
                    if (a!=NULL)
                    {
                        printf("Nombre de mots total : %d\nNombre de noeuds : %d\nProfondeur de l'arbre : %d\n",a->nb_mots_total,a->nb_mots_differents,hauteur_arbre(a));
                        if (est_equilibre(a->racine)) printf("Arbre equilibre.\n\n");
                        else
                            printf("Arbre non equilibre.\n\n");
                    }
                    else
                        printf("Impossible ! Arbre non cree !\n\n");
                    break;

            /*Afficher mots distincts*/
            case 4:
                    if (a!=NULL)
                    {
                        afficher_arbre(*a);
                        printf("\n");
                    }
                    else
                        printf("Impossible ! Arbre non cree !\n\n");
                    break;

            /*Rechercher un mot*/
            case 5:
                    if (a!=NULL)
                    {
                        printf("\nVeuillez saisir le mot a rechercher : ");
                        scanf("%s",mot);
                        mot2=StringToLower(mot);
                        char* nom1 = (char*)malloc(strlen(mot2));
                        memcpy(nom1, mot2, strlen(mot2)+1);
                        NoeudABR* x=rechercher_noeud(a,nom1);
                        afficher_position(x);
                    }
                    else
                       printf("Impossible ! Arbre non cree !\n\n");
                    break;

            /*Recherche de phrase à partir de 2 mots*/
            case 6:
                    if (a!=NULL)
                    {
                        if(fichier_charge)
                        {
                            printf("Veuillez saisir les mots recherches : ");
                            scanf("%s %s",mot, mot1);
                            afficher_phrases(a,mot,mot1,filename);
                        }
                        else
                            printf("Impossible ! Aucun fichier charge dans l'ABR.\n\n");
                    }
                    else
                    {
                        printf("Impossible ! Arbre non cree.\n\n");
                    }
                    break;

            /*Affichage d'un fichier texte */
            case 7:
                    printf("Veuillez saisir le fichier a afficher en chemin relatif ou absolu : ");
                    scanf("%s",filename2);
                    afficher_fichier(filename2);
                    break;

            /*Quitter le programme et rendre les allocations */
            case 8:
                    free(filename); free(filename2); free(mot); free(mot1);
                    free_arbre(a, a->racine);
                    printf("Au revoir !\n");
                    return 0;

            default:
                     printf("Commande non reconnue.\n\n");
                     break;
        }
    }
}
