/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:47:56 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/27 12:38:37 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// implementer le changement de wd ou pas ?
int	ft_cd(char *path)
{
	if (!path)
	{
		char *home;
		
		home = getenv("HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		if (chdir(home) == -1)
		{
			error();
			return (1);
		}
		return (0);
	}
	if (chdir(path) == -1)
	{
		error();
		return (1);
	}
	return (0);
}

