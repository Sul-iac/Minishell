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

char	*process_input(const char *inp, size_t *i,
	size_t *j, char *result, size_t *k)
{
	char	*var_value;
	size_t	value_len;

	while (inp[*i] != '\0')
	{
		if (inp[*i] == '$' && inp[*i + 1] && inp[*i + 1] != ' ' && inp[*i + 1] != '\t')
		{
			(*i)++;
			var_value = get_env_variable_value(inp, i);
			if (var_value)
			{
				value_len = strlen(var_value);
				result = resize_result_if_needed(result, k, *j + value_len);
				if (!result)
				{
					return (NULL);
				}
				strcpy(&result[*j], var_value);
				*j += value_len;
			}
		}
		else
			result[(*j)++] = inp[(*i)++];
	}
	return (result);
}

char	*expand_env_variables(const char *input)
{
	size_t	result_size;
	char	*result;
	size_t	i;
	size_t	j;
	char	*var_value;

	j = 0;
	i = 0;
	result = (char *)malloc(result_size);
	result_size = 1024;
	if (!result)
		return (NULL);
	result = process_input(input, &i, &j, result, &result_size);
	if (!result)
		return (NULL);
	result[j] = '\0';
	return (result);
}

void	expand_node_values(t_node *head)
{
	t_node	*current;
	char	*expanded_value;

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

void	ft_expenser(t_node *head)
{
	mark_builtins(head);
	ft_is_last_cmd(head);
	expand_node_values(head);
}
