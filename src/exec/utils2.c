/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 19:29:53 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/02 16:08:27 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_free_array(char **array)
{
    size_t  i;

    if (!array)
        return;
    i = 0;
    while (array[i])
    {
        free(array[i]);
        array[i] = NULL;
        i++;
    }
    free(array);
}

void	ft_free(void *ptr)
{
	free(ptr);
}

void	free_and_error(char *ptr, char **ptr2, char *msg, bool error)
{
	if(ptr)
		ft_free(ptr);
	if(ptr2)
		ft_free_array(ptr2);
	if(error)
	{
		printf("%s", msg);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}