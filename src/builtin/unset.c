/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:21:05 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/30 19:08:00 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// Dans unset.c
char **ft_unset(char *arg, char ***env)
{
    int     i;
    int     j;
    char    **new_env;
    char    *env_name;

    if (!arg || !*env || !is_valid_identifier(arg))
        return (*env);
    i = 0;
    while ((*env)[i])
        i++;
    new_env = malloc(sizeof(char *) * i);
    if (!new_env)
        return (*env);
    i = 0;
    j = 0;
    while ((*env)[i])
    {
        env_name = get_var_name((*env)[i]);
        if (!env_name)
        {
            ft_free_array(new_env);
            return (*env);
        }
        if (ft_strcmp(env_name, arg) != 0)
        {
            new_env[j] = strdup((*env)[i]);
            if (!new_env[j])
            {
                free(env_name);
                ft_free_array(new_env);
                return (*env);
            }
            j++;
        }
        free(env_name);
        i++;
    }
    new_env[j] = NULL;
	*env = new_env;
	// i = -1;
	// while(env[++i])
	// 	printf("%s\n", env[i]);
	return(*env);
}
