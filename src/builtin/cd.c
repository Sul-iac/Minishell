#include "../../includes/minishell.h"

void    ft_cd(char *args)
{
    // il faudra ici, soit que l'on mette dans les arguments de la fonctions, 
    // les OPTIONS (e.g "..", ou "/home/[...]") fait par le lexer ou alors concatener les variables 
    // d'environnements avec gentev(). 
    (void)args;
    char *env_p = getenv("HOME");        //prend la variable d'environnement a partir du dossier courrant
    char *delimiter = ":";
    // char *path = strtok(env_p, delimiter);   
    // on pourrait utiliser strcat() afin de concatener l'option (cd /documents) avec 
    // le repertoire home. Ensuite, je pourrais utiliser le chemin donne dans la fonction chdir().
    // il faut d'abord que je creer le lexer afin de pouvoir envoyer les differents tokens
    chdir("..");
    
}