#ifndef OUTILS_H_INCLUDED
#define OUTILS_H_INCLUDED

/*Déclaration des différentes fonctions utiles pour permettre le bon fonctionnement du programme*/
NoeudABR* creer_noeud();
char* StringToLower(char* str);
int my_strcmp(char* str1,char* str2);
int ajouter_mot(ArbreBR *arbre, char* mot, int ligne, int ordre, int num_phrase);
void afficher_noeud(NoeudABR* x);
int maxi(int a,int b);
int hauteur(NoeudABR* noeud);
int hauteur_arbre(ArbreBR* arbre);
int abs(int a);
int equilibre_noeud(NoeudABR* noeud);
int est_equilibre(NoeudABR* noeud);
void afficher_position(NoeudABR* noeud);
void afficher_fichier(char* filename);
void afficher_phrase_occurence(int num_phrase, char* filename);
void afficher_phrases(ArbreBR* arbre,char* mot1, char* mot2,char* filename);
void free_arbre (ArbreBR * arbre, NoeudABR * noeud);
void free_noeud (NoeudABR * noeud);

#endif // OUTILS_H_INCLUDED
