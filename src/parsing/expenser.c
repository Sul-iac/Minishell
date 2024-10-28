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

char	*expand_env_variables(const char *input)
{
	size_t	result_size;
	char	*result;
	size_t	i;
	size_t	j;
	size_t	var_len;
	char	*var_name;
	char	*var_value;
	size_t	value_len;

	result_size = 1024;
	result = (char *)malloc(result_size);
	i = 0;
	j = 0;
	if (!result)
		return (NULL);
	while (input[i] != '\0')
	{
		if (input[i] == '$' && (input[i + 1] != ' '
				&& input[i + 1] != '\t' && input[i + 1] != '\0'))
		{
			i++;
			var_len = 0;
			while (input[i + var_len] && (input[i + var_len] != ' '
					&& input[i + var_len] != '\t' && input[i + var_len] != '$'))
			{
				var_len++;
			}
			var_name = strndup(&input[i], var_len);
			if (!var_name)
			{
				free(result);
				return (NULL);
			}
			var_value = getenv(var_name);
			free(var_name);
			if (var_value)
			{
				value_len = strlen(var_value);
				if (j + value_len >= result_size)
				{
					result_size *= 2;
					result = (char *)realloc(result, result_size);
					if (!result)
						return (NULL);
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

void	free_nodes(t_node *head)
{
	t_redirection	*temp_output;
	t_node			*temp;
	t_redirection	*input;
	t_redirection	*temp_input;
	t_redirection	*output;

	while (head)
	{
		temp = head;
		head = head->next;
		if (temp->value)
		{
			free(temp->value);
		}
		input = temp->inputs;
		while (input)
		{
			temp_input = input;
			input = input->next;
			free(temp_input->filename);
			free(temp_input);
		}
		output = temp->outputs;
		while (output)
		{
			temp_output = output;
			output = output->next;
			free(temp_output->filename);
			free(temp_output);
		}
		free(temp);
	}
}

void	ft_expenser(t_node *head)
{
	mark_builtins(head);
	ft_is_last_cmd(head);
	expand_node_values(head);
}
