/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:26:15 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/29 14:26:15 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**split_string(const char *input)
{
	int			num_pipes;
	const char	*ptr;
	int			j;
	char		**str_array;
	size_t		start;
	int			index;
	const char	*pipe_pos;
	size_t		length;

	ptr = input;
	num_pipes = 0;
	while (*ptr != '\0')
	{
		if (*ptr == '|')
		{
			num_pipes++;
		}
		ptr++;
	}
	str_array = malloc((num_pipes + 2) * sizeof(char *));
	if (str_array == NULL)
	{
		return (NULL);
	}
	start = 0;
	index = 0;
	while (index <= num_pipes)
	{
		pipe_pos = strchr(input + start, '|');
		if (pipe_pos != NULL)
		{
			length = (size_t)(pipe_pos - (input + start));
		}
		else
		{
			length = strlen(input + start);
		}
		str_array[index] = malloc((length + 1) * sizeof(char));
		if (str_array[index] == NULL)
		{
			j = 0;
			while (j < index)
			{
				free(str_array[j]);
				j++;
			}
			free(str_array);
			return (NULL);
		}
		strncpy(str_array[index], input + start, length);
		str_array[index][length] = '\0';
		start += length + 1;
		index++;
	}
	str_array[index] = NULL;
	return (str_array);
}

void	free_tokens(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->value);
		free(temp);
	}
}

t_token	*concat_tokens(t_token *head1, t_token *head2)
{
	t_token	*current;
	t_token	*pipe_token;

	if (!head1)
		return (head2);
	if (!head2)
		return (head1);
	current = head1;
	while (current->next)
	{
		current = current->next;
	}
	pipe_token = create_token("|", PIPE);
	current->next = pipe_token;
	current->next->next = head2;
	return (head1);
}
