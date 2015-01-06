#include "liste.h"
#include "arbre.h"
#include "outils.h"

int main()
{
    int choix=0;
    char nom_fichier[30], mot_tmp[20];
    ArbreBR * arbre;
    NoeudABR * noeud_tmp;

    /*Affichage de l'en-tete du programme */
    printf("\tBienvenue dans votre programme de classement alphabétique de texte\n\n");

    while (choix != 7){
        while ((choix < 1) || (choix >7)){
            printf("\n");
            afficher_separateurs(70);
            printf("Selectionner une fonction :\n\n");
            printf("1 - Creer un ABR\n");
            printf("2 - Charger un fichier dans l'ABR\n");
            printf("3 - Afficher les caractériqtiques de l'ABR\n");
            printf("4 - Afficher tous les mots distincts par ordre alphabetique\n");
            printf("5 - Rechercher un mot\n");
            printf("6 - Afficher toutes les phrases contenant 2 mots saisis\n");
            printf("7 - Quitter\n");
            afficher_separateurs(70);

            scanf("%d", &choix);
        }
        switch (choix){
            /*Création ABR*/
            case 1 :
                arbre = creer_ABR();
                printf("\nABR cree\n");
                choix = 0;
                break;

            /*Charger un fichier*/
            case 2 :
                printf("\nDonnez le nom du fichier à charger (ou son chemin complet s'il n'est pas dans le dossier courant) : ");
                scanf("%s", nom_fichier);
                if (charger_fichier(arbre, nom_fichier) != 0)
                    printf("Fichier chargé avec succès dans l'ABR\n");
                choix = 0;
                break;

            /*Afficher caractériqtiques ABR*/
            case 3 :
                printf("\nL'ABR contient %d mots différents et %d mots au total.\n", arbre->nb_mots_differents, arbre->nb_mots_total);
                choix = 0;
                break;

            /*Afficher mots distincts*/
            case 4 :
                printf("\nListe des mots du texte analysé :\n");
                afficher_arbre(*arbre);
                choix = 0;
                break;

            /*Rechercher un mot*/
            case 5 :
                printf("\nEntrez le mot que vous recherchez : ");
                scanf("%s", mot_tmp);
                format_str(mot_tmp);
                noeud_tmp = rechercher_noeud(arbre, mot_tmp);
                if (noeud_tmp != NULL){
                    printf("Les positions de '%s' sont : \n", mot_tmp);
                    afficher_positions(noeud_tmp->positions);
                }
                else
                    printf("Ce mot n'est pas dans le texte\n");
                choix = 0;
                break;

            default : break;
        }

    }

    return 0;
}
