/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expenser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:47:17 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/28 15:47:17 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool ft_is_builtin(char *command)
{
    if (command == NULL) return false;
    
    const char *builtins[] = {"echo ", "cd ", "pwd ", "export ", "unset ", "env ", "exit "};
    unsigned long i = 0;

    while (i < 7)
    {
        if (strstr(command, builtins[i]) != NULL)
        {
            return true;
        }
        i++;
    }
    return false;
}

void mark_builtins(t_node *head)
{
    t_node *current = head;

    while (current != NULL)
    {
        if (ft_is_builtin(current->value))
        {
            current->builtin = true;
        }
        else
        {
            current->builtin = false;
        }
        current = current->next;
    }
}

void ft_is_last_cmd(t_node *head)
{
    if (head == NULL)
    {
        return;
    }

    t_node *current = head;

    while (current != NULL)
    {
        if (current->next == NULL)
        {
            current->is_last_cmd = 1;
        }
        else
        {
            current->is_last_cmd = 0;
        }
        current = current->next;
    }
}

char *expand_env_variables(const char *input)
{
    size_t result_size = 1024;
    char *result = (char *)malloc(result_size);
    if (!result) return NULL;

    size_t i = 0;
    size_t j = 0;

    while (input[i] != '\0')
    {
        if (input[i] == '$' && (input[i+1] != ' ' && input[i+1] != '\t' && input[i+1] != '\0'))
        {
            i++;
            size_t var_len = 0;
            while (input[i + var_len] && (input[i + var_len] != ' ' && input[i + var_len] != '\t' && input[i + var_len] != '$'))
            {
                var_len++;
            }

            char *var_name = strndup(&input[i], var_len);
            if (!var_name) {
                free(result);
                return NULL;
            }
            char *var_value = getenv(var_name);
            free(var_name);

            if (var_value)
            {
                size_t value_len = strlen(var_value);
                if (j + value_len >= result_size)
                {
                    result_size *= 2;
                    result = (char *)realloc(result, result_size);
                    if (!result) return NULL;
                }
                strcpy(&result[j], var_value);
                j += value_len;
            }
            i += var_len;
        }
        else
        {
            result[j++] = input[i++];
        }
    }

    result[j] = '\0';
    return result;
}

void expand_node_values(t_node *head)
{
    t_node *current = head;
    while (current != NULL) {
        if (current->type == CMD_2 && current->value != NULL)
        {
            char *expanded_value = expand_env_variables(current->value);
            if (expanded_value)
            {
                free(current->value);
                current->value = expanded_value;
            }
        }
        current = current->next;
    }
}

void free_nodes(t_node *head)
{
    while (head)
    {
        t_node *temp = head;
        head = head->next;
        
        if (temp->value)
        {
            free(temp->value);
        }
        
        t_redirection *input = temp->inputs;
        while (input)
        {
            t_redirection *temp_input = input;
            input = input->next;
            free(temp_input->filename);
            free(temp_input);
        }

        t_redirection *output = temp->outputs;
        while (output)
        {
            t_redirection *temp_output = output;
            output = output->next;
            free(temp_output->filename);
            free(temp_output);
        }

        free(temp);
    }
}
void ft_expenser(t_node *head)
{
    mark_builtins(head);
    ft_is_last_cmd(head);
    expand_node_values(head);
}
