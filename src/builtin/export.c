/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:09:03 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/27 14:21:20 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


char *no_args(char **str)
{
	//...
}


// export seul display les variables d'env dans l'ordre alphabetique
// export avec args set une nouvelle variable dans l'env
void    ft_export(char *args, char **env)
{
	int	i;
	int len;
    char **new_env;

	len = -1;
	i = -1;	
	printf("export: %s\n", args);
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
	if(!args)
	{
		while(env[++i])
			printf("declare -x %s\n", env[i]);
	}
	else
	{
		error();
	}
}
