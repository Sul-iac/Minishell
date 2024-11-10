/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:21:05 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/10 22:35:24 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process_unset(char **new_env, char ***env, char *arg, int *j)
{
	int		i;
	char	*env_name;

	i = 0;
	while ((*env)[i])
	{
		env_name = get_var_name((*env)[i]);
		if (!env_name)
		{
			ft_free_array(new_env);
			return ;
		}
		if (ft_strcmp(env_name, arg) != 0)
		{
			new_env[*j] = strdup((*env)[i]);
			(*j)++;
		}
		free(env_name);
		i++;
	}
	new_env[*j] = NULL;
	*env = new_env;
}

char	**ft_unset(char *arg, char ***env)
{
	int		i;
	int		j;
	char	**new_env;

	if (!arg || !*env || !is_valid_identifier(arg))
		return (*env);
	i = 0;
	while ((*env)[i])
		i++;
	new_env = malloc(sizeof(char *) * i);
	if (!new_env)
		return (*env);
	j = 0;
	process_unset(new_env, env, arg, &j);
	return (*env);
}
