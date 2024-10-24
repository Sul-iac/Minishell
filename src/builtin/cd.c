/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:46:44 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/24 21:11:10 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    ft_cd(char **cmd)
{
	char *path;

	if(!cmd[1])
	{
		path = getenv("HOME");
		if(!path)
		{
			printf("cd: HOME not set\n", 2);
			return(1);
		}
	}
	else
		path = cmd[1];
	if(chdir(path) == -1)
	{
		printf("cd: %s: No such path or directory\n");
		return(1);
	}
	return(0);
}

