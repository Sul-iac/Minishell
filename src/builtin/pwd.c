#include "../../includes/minishell.h"

void    ft_pwd(char *args)
{
    (void)args;
    char wd[1000];
    printf("%s\n", getcwd(wd, sizeof(wd)));
}