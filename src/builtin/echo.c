#include "../../includes/minishell.h"

void ft_echo(int argc, char **argv, char **envp)
{
    (void)envp;
    int newline = 1;
    int i = 1;

    if (i < argc && strcmp(argv[i], "-n") == 0)
    {
        newline = 0;
        i++;
    }
    while (i < argc)
    {
        printf("%s", argv[i]);
        i++;
        if (i < argc)
        {
            printf(" ");
        }
    }
    if (newline)
    {
        printf("\n");
    }
}
