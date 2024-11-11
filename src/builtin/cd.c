/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 11:47:56 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/11 02:44:04 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_cd(char *path)
{
	char	*home;

	if (!path)
	{
		home = getenv("HOME");
		if (!home)
			free_and_error(NULL, NULL, "Home not set", 1);
		if (chdir(home) == -1)
			free_and_error(NULL, NULL, "cd: Home nout found", 1);
		return (0);
	}
	if (chdir(path) == -1)
	{
		perror("cd");
		free(path);
	}
	return (0);
}
