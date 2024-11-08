/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:09:05 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/08 20:19:08 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_number(const char *str)
{
    int i = 0;

    if (str[0] == '-')
        i++;
    while (str[i] != '\0')
	{
        if (!isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int	ft_exit(char **arg)
{
    if (arg[1])
	{
        if (!is_number(arg[1]))
		{
            printf("exit: %s: numeric argument required\n", arg[1]);
			return(-1);		
		}
		else
			return(0);
        if (arg[2] != NULL)
		{
			free_and_error(NULL, arg, "exit: too many arguments", 1);
			return(-1);
		}
    }
    free(arg);
    printf("exit\n");
	exit(0);
}
