#include "liste.h"
#include "arbre.h"
#include "outils.h"

int main()
{
    char s[15] ="Hello WorLd!";
    printf("%s\n",s);
    format_str(s);
    printf("%s\n",s);
    return 0;
}
