#include "outils.h"

void format_str (char * s)
{
    int i = 0, l;

    for (i = 0, l = strlen(s) ; i<l ; i++)
    {
        if (s[i]<='Z' && s[i]>='A')
            s[i] = s[i] - 'A' + 'a';
    }
}

int charger_fichier (ArbreBR * arbre, char * filename) {
    FILE * fichier = NULL;
    fichier = fopen(filename, "r");

    if (fichier == NULL) {
        printf("Le fichier %s n'existe pas.\n", filename);
        return 0;
    }

    int i = 0, ligne = 1, ordre = 1, num_phrase = 1;
    char c = fgetc(fichier), *s = malloc(sizeof(char)*30);

    while (c != EOF){
        i = 0;
        while ((c != ' ') && (c != '\n') && (c != ',') && (c != ';') && (c != '.') && (c != '!') && (c != '?')) {
            s[i] = c;
            i++;
            c = fgetc(fichier);
        }
        s[i] = '\0';

        ajouter_mot(arbre, s, ligne, ordre, num_phrase);


        while ((c == ' ') || (c == '\n') || (c == ',') || (c == ';') || (c == '.') || (c == '!') || (c == '?')) { //On passse tous les caractères non alphanumériques
            if ((c == '.') || (c == '!') || (c == '?'))
                num_phrase++;
            if (c == '\n')
                ligne++;
            c = fgetc(fichier);
        }
        ordre++;

    }
    free(s);
    return 1;

}

void afficher_separateurs(int x) // Fonction esthétique servant a afficher les séparateurs pour le menu
{
    int i = 0;
    for (i = 0 ; i<x ; i++)
        printf("-");
    printf("\n");
}
