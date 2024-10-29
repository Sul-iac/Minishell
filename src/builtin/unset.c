/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:21:05 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/29 17:07:50 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int is_valid_identifier(const char *var)
{
    int i;

    if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
        return (0);
    i = 0;
    while (var[i])
    {
        if (!ft_isalnum(var[i]) && var[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

static char *get_var_name(const char *var)
{
    int     i;
    char    *name;

    i = 0;
    while (var[i] && var[i] != '=')
        i++;
    name = ft_substr(var, 0, i);
    return (name);
}
// Dans unset.c
char **ft_unset(char *arg, char **env)
{
    int     i;
    int     j;
    char    **new_env;
    char    *var_name;
    char    *env_name;

    if (!arg || !env || !is_valid_identifier(arg))
	{
		printf("Fin de fonction unset\n");
        return (env);
	}
    i = 0;
    while (env[i])
        i++;
    new_env = malloc(sizeof(char *) * i);
    if (!new_env)
        return env;
    i = 0;
    j = 0;
    while (env[i])
    {
        env_name = get_var_name(env[i]);
        if (!env_name)
        {
            ft_free_array(new_env);
            return env;
        }
        if (ft_strcmp(env_name, arg) != 0)
        {
            new_env[j] = strdup(env[i]);
            if (!new_env[j])
            {
                free(env_name);
                ft_free_array(new_env);
                return env;
            }
            j++;
        }
        else
            printf("unsetting: %s\n", arg);
        free(env_name);
        i++;
    }
    new_env[j] = NULL;
    // ft_free_array(env);
	env = new_env;
	return(env);
}
