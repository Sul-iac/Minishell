/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expenser_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:13:14 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/29 13:13:14 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *get_env_variable_value(const char *input, size_t *i)
{
    size_t var_len;
    char *var_name;
    char *var_value;

    var_len = 0;
    while (input[*i + var_len] && input[*i + var_len] != ' '
        && input[*i + var_len] != '\t' && input[*i + var_len] != '$'
        && input[*i + var_len] != '\'' && input[*i + var_len] != '\"')
    {
        var_len++;
    }
    var_name = strndup(&input[*i], var_len);
    if (!var_name)
        return (NULL);
    var_value = getenv(var_name);
    free(var_name);
    *i += var_len;
    return (var_value);
}

char *process_input(const char *p, t_process_data *data, char *result)
{
    char *var_value;
    size_t value_len;
    int in_single_quote = 0;
    int in_double_quote = 0;

    while (p[data->i] != '\0')
    {
        // Gestion des guillemets simples et doubles
        if (p[data->i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            data->i++;  // Ne pas inclure le guillemet simple dans le résultat
            continue;
        }
        else if (p[data->i] == '\"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            data->i++;  // Ne pas inclure le guillemet double dans le résultat
            continue;
        }
        
        // Expansion des variables seulement si on n'est pas entre guillemets simples
        if (p[data->i] == '$' && p[data->i + 1] && p[data->i + 1] != ' ' && p[data->i + 1] != '\t' && !in_single_quote)
        {
            data->i++;
            var_value = get_env_variable_value(p, &data->i);
            if (var_value)
            {
                value_len = strlen(var_value);
                result = resize_result_if_needed(result, &data->k, data->j + value_len);
                if (!result)
                    return (NULL);
                strcpy(&result[data->j], var_value);
                data->j += value_len;
            }
        }
        else
        {
            // Copier les caractères normaux ou les caractères dans des guillemets simples
            result = resize_result_if_needed(result, &data->k, data->j + 1);
            if (!result)
                return (NULL);
            result[data->j++] = p[data->i++];
        }
    }
    return (result);
}

char *expand_env_variables(const char *input)
{
    size_t result_size = 1024;
    char *result;
    t_process_data data;

    data.j = 0;
    data.i = 0;
    data.k = result_size;
    result = (char *)malloc(result_size);
    if (!result)
        return (NULL);
    
    result = process_input(input, &data, result);
    if (!result)
        return (NULL);
    
    result[data.j] = '\0';
    return (result);
}

void expand_node_values(t_node *head)
{
    t_node *current;
    char *expanded_value;

    current = head;
    while (current != NULL)
    {
        if (current->type == CMD_2 && current->value != NULL)
        {
            expanded_value = expand_env_variables(current->value);
            if (expanded_value)
            {
                free(current->value);
                current->value = expanded_value;
            }
        }
        current = current->next;
    }
}

char *resize_result_if_needed(char *result, size_t *result_size, size_t required_size)
{
    if (required_size >= *result_size)
    {
        *result_size *= 2;
        result = (char *)realloc(result, *result_size);
        if (!result)
            return (NULL);
    }
    return (result);
}
