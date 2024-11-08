/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:17:25 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/08 20:35:21 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_valid_identifier(const char *var)
{
    int i;

    if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
        return (0);
    i = 1;
    while (var[i] && var[i] != '=')
    {
        if (!ft_isalnum(var[i]) && var[i] != '_')
            return (0);
        i++;
    }
    return (1);
}

char *get_var_name(const char *var)
{
    int i;
    char *name;

    i = 0;
    while (var[i] && var[i] != '=')
        i++;
    name = ft_substr(var, 0, i);
    return (name);
}

int var_exists(char ***env, char *var_name)
{
    int i;
    char *name;

    i = -1;
    while ((*env)[++i])
    {
        name = get_var_name((*env)[i]);
        if (ft_strcmp(name, var_name) == 0)
        {
            free(name);
            return (i);
        }
        free(name);
    }
    return (-1);
}

void sort_env(char ***env)
{
    int     i;
    int     j;
    char    *temp;
    int     len;

    len = 0;
    while ((*env)[len])
        len++;
    i = -1;
    while (++i < len - 1)
    {
        j = -1;
        while (++j < len - i - 1)
        {
            if (ft_strcmp((*env)[j], (*env)[j + 1]) > 0)
            {
                temp = (*env)[j];
                (*env)[j] = (*env)[j + 1];
                (*env)[j + 1] = temp;
            }
        }
    }
}

void display_sorted_env(char **env)
{
    int     i;
    int     len;
    char    **env_copy;

    len = 0;
    while (env[len])
        len++;
    env_copy = malloc(sizeof(char *) * (len + 1));
    if (!env_copy)
       free_and_error(NULL, env_copy, "Display_sorted_env: env_copy malloc error", 1);
    i = -1;
    while (env[++i])
    {
        env_copy[i] = strdup(env[i]);
        if (!env_copy[i])
			free_and_error(NULL, env_copy, "Display_sorted_env: env_copy error", 1);
    }
    env_copy[i] = NULL;
    sort_env(&env_copy);
    i = -1;
    while (env_copy[++i])
        printf("declare -x %s\n", env_copy[i]);
    ft_free_array(env_copy);
}

// Dans export.c
char **ft_export(char *args, char ***env)
{
    int     i;
    int     env_size;
    char    **new_vars;
    char    *var_name;
    int     var_pos;

    if (!args)
	{
        display_sorted_env(*env);
		return(*env);
	}
    env_size = 0;
    while ((*env)[env_size])
        env_size++;
    new_vars = ft_split(args, ' ');
    if (!new_vars)
        free_and_error(NULL, new_vars, "export: error splitting arguments", 1);
    i = 0;
    while (new_vars[i])
        i++;
    i = -1;
    while (new_vars[++i])
    {
        if (!is_valid_identifier(new_vars[i]))
            continue;
        var_name = get_var_name(new_vars[i]);
        var_pos = var_exists(env, var_name);
        if (var_pos != -1)
        {
            free((*env)[var_pos]);
            (*env)[var_pos] = strdup(new_vars[i]);
        }
        else
        {
            (*env)[env_size] = strdup(new_vars[i]);
            (*env)[env_size + 1] = NULL;
            env_size++;
        }
        free(var_name);
    }
    ft_free_array(new_vars);
    return(*env);
}
