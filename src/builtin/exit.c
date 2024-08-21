#include "../../includes/minishell.h"

void    ft_exit(char *line)
{
    if (strcmp(line, "exit\n") == 0)
    {
        free(line);
        exit(EXIT_SUCCESS);
    }
}