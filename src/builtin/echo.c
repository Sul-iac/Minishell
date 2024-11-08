/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:09:46 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/08 15:39:30 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_echo(char **args)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
    if (args[1] && strcmp(args[1], "-n") == 0)
	{
        newline = 0;
        i = 2;
    }
    while(args[i]) 
	{
        printf("%s", args[i]);
        if (args[i + 1])
            printf(" ");
		i++;
    }
    if (newline) 
        printf("\n");
}

