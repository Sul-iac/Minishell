/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expenser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:47:17 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/28 16:36:42 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_builtin(char *command)
{
	const char		*builtins[] = {"echo ", "cd ", "pwd ", "export ",
		"unset ", "env ", "exit "};
	unsigned long	i;

	i = 0;
	if (command == NULL)
		return (false);
	while (i < 7)
	{
		if (strstr(command, builtins[i]) != NULL)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

void	mark_builtins(t_node *head)
{
	t_node	*current;

	current = head;
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

void	ft_is_last_cmd(t_node *head)
{
	t_node	*current;

	current = head;
	if (head == NULL)
	{
		return ;
	}
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

char	*get_env_variable_value(const char *input, size_t *i)
{
	size_t	var_len;
	char	*var_name;
	char	*var_value;

	var_len = 0;
	while (input[*i + var_len] && input[*i + var_len] != ' '
		&& input[*i + var_len] != '\t' && input[*i + var_len] != '$')
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

char	*resize_result_if_needed(char *result,
	size_t *result_size, size_t required_size)
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
