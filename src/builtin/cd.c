/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 20:46:44 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/24 21:39:01 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int    ft_cd(char *args)
{
	char *path;
	
	if(!args[1])
	{
		path = getenv("HOME");
		if(!path)
		{
			printf("cd: HOME not set\n");
			return(1);
		}
	}
	if(chdir(args) == -1)
	{
		printf("cd: %s: No such file or directory\n");
		return(1);
	}
}

