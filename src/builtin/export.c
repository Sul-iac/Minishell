/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 09:17:25 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/29 17:47:24 by qbarron          ###   ########.fr       */
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

int var_exists(char **env, char *var_name)
{
    int i;
    char *name;

    i = 0;
    while (env[i])
    {
        name = get_var_name(env[i]);
        if (ft_strcmp(name, var_name) == 0)
        {
            free(name);
            return (i);
        }
        free(name);
        i++;
    }
    return (-1);
}

void sort_env(char **env)
{
    int     i;
    int     j;
    char    *temp;
    int     len;

    len = 0;
    while (env[len])
        len++;
    i = 0;
    while (i < len - 1)
    {
        j = 0;
        while (j < len - i - 1)
        {
            if (ft_strcmp(env[j], env[j + 1]) > 0)
            {
                temp = env[j];
                env[j] = env[j + 1];
                env[j + 1] = temp;
            }
            j++;
        }
        i++;
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
        return (error());
    i = -1;
    while (env[++i])
    {
        env_copy[i] = strdup(env[i]);
        if (!env_copy[i])
        {
            ft_free_array(env_copy);
        	error();
        }
    }
    env_copy[i] = NULL;
    sort_env(env_copy);
    i = -1;
    while (env_copy[++i])
        printf("declare -x %s\n", env_copy[i]);
    ft_free_array(env_copy);
}

// Dans export.c
char **ft_export(char *args, char **env)
{
    int     i;
    int     env_size;
    char    **new_env;
    char    **new_vars;
    char    *var_name;
    int     var_pos;

    if (!args)
        display_sorted_env(env);

    env_size = 0;
    while (env[env_size])
        env_size++;

    new_vars = ft_split(args, ' ');
    if (!new_vars)
        error();
    i = 0;
    while (new_vars[i])
        i++;
    new_env = malloc(sizeof(char *) * (env_size + i + 1));
    if (!new_env)
    {
        ft_free_array(new_vars);
        error();
    }
    i = -1;
    while (env[++i])
    {
        new_env[i] = strdup(env[i]);
        if (!new_env[i])
        {
            ft_free_array(new_vars);
            ft_free_array(new_env);
            error();
        }
    }
    i = -1;
    while (new_vars[++i])
    {
        if (!is_valid_identifier(new_vars[i]))
            continue;
        var_name = get_var_name(new_vars[i]);
        var_pos = var_exists(env, var_name);
        if (var_pos != -1)
        {
            free(env[var_pos]);
            env[var_pos] = strdup(new_vars[i]);
        }
        else
        {
            env[env_size] = strdup(new_vars[i]);
            env[env_size + 1] = NULL;
            env_size++;
        }
        free(var_name);
    }
    ft_free_array(new_vars);
	// display_sorted_env(env);
    return(env);
}
