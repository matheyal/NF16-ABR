#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

/*Définition de la structure NoeudABR contenant le champ mot,
une liste des positions des mots dans le texte et d'un pointeur sur les noeuds fils droit et fils gauche*/
typedef struct NoeudABR
{
    char* mot;
    ListePosition positions;
    struct NoeudABR* filsGauche;
    struct NoeudABR* filsDroit;
}NoeudABR;

/*Définition de la structure ArbreBR qui contient le champ racine qui contient le noeud racine de l'arbre, et un champ nb_mots_différents qui
contient le nombre de noeuds, et le champ nb_mots_total qui contient le nombre de mots total du fichier*/
typedef struct ArbreBR
{
    NoeudABR* racine;
    int nb_mots_differents;
    int nb_mots_total;
}ArbreBR;

/*Déclaration des différentes fonctions relatives à la gestion de l'arbre*/
ArbreBR *creer_abr();
int ajouter_noeud(ArbreBR *arbre, NoeudABR *noeud);
int charger_fichier(ArbreBR *arbre, char *filename);
NoeudABR* rechercher_noeud(ArbreBR *arbre, char *mot);
void afficher_arbre(ArbreBR arbre);

#endif // ARBRE_H_INCLUDED
