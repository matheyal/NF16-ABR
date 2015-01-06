#include "liste.h"
#include "arbre.h"
#include "outils.h"

int main()
{
    ArbreBR * arbre = creer_ABR();

    charger_fichier(arbre, "texte.txt");
    afficher_arbre(*arbre);
    return 0;
}
