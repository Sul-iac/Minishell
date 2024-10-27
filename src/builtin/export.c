/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:09:03 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/27 15:34:16 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// export seul display les variables d'env dans l'ordre alphabetique
// export avec args set une nouvelle variable dans l'env

static int check_errors(char **new_env)
{
	
}

void    ft_export(char *args, char **env)
{
	int	i;
	int len;
    char **new_env;
	char **new_var;
	len = -1;
	i = -1;
	while(env[++len]);
	new_env = malloc(sizeof(char *) * (len + 2));
	if(!new_env)
		error();
	i = -1;
	while(env[++i])
	{
		new_env[i] = strdup(env[i]);
		if(!new_env[i])
			error();
	}
	new_env[i] = NULL;
	i = -1;
	while(env[++i])
		free(env[i]);
	i = -1;
	if(!args)
	{
		while(new_env[++i])
			printf("declare -x %s\n", new_env[i]);
	}
	else
	{
		i = -1;
		new_var = ft_split(args, ' ');
		while(new_var[++i])
		{
			if(check_errors(new_var) == 0) // test=bonjour
			{
				
			}
			else
				error();
		}
		i = -1;
		while(new_env[++i])
			printf("declare -x %s\n", new_env[i]);
	}
}
