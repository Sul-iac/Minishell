/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 21:46:37 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/10 23:23:49 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	export_utils(char **new_vars, char ***env, int env_size, int *i)
{
	char	*var_name;
	int		var_pos;

	while (new_vars[++(*i)])
	{
		if (!is_valid_identifier(new_vars[(*i)]))
			continue ;
		var_name = get_var_name(new_vars[(*i)]);
		var_pos = var_exists(env, var_name);
		if (var_pos != -1)
		{
			free((*env)[var_pos]);
			(*env)[var_pos] = strdup(new_vars[(*i)]);
		}
		else
		{
			(*env)[env_size] = strdup(new_vars[(*i)]);
			(*env)[env_size + 1] = NULL;
			env_size++;
		}
		free(var_name);
	}
}

void	display_sorted_env(char **env)
{
	int		i;
	int		len;
	char	**env_copy;

	len = 0;
	while (env[len])
		len++;
	env_copy = malloc(sizeof(char *) * (len + 1));
	if (!env_copy)
		free_and_error(NULL, env_copy,
			"Display_sorted_env: env_copy malloc error", 1);
	i = -1;
	while (env[++i])
	{
		env_copy[i] = strdup(env[i]);
		if (!env_copy[i])
			free_and_error(NULL, env_copy, "Display_sorted_env: env_copy error",
				1);
	}
	env_copy[i] = NULL;
	sort_env(&env_copy);
	i = -1;
	while (env_copy[++i])
		printf("declare -x %s\n", env_copy[i]);
	ft_free_array(env_copy);
}
