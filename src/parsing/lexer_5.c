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

int	count_pipes(const char *input)
{
	int			num_pipes;
	int			in_quotes;
	const char	*ptr;

	num_pipes = 0;
	in_quotes = 0;
	ptr = input;
	while (*ptr != '\0')
	{
		if (*ptr == '"')
			in_quotes = !in_quotes;
		if (*ptr == '|' && !in_quotes)
			num_pipes++;
		ptr++;
	}
	return (num_pipes);
}

char	*allocate_and_copy(const char *start, size_t length)
{
	char	*new_str;

	new_str = malloc((length + 1) * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	strncpy(new_str, start, length);
	new_str[length] = '\0';
	return (new_str);
}

char	**split_into_array(const char *input, int num_pipes)
{
	char		**str_array;
	size_t		start;
	int			index;
	const char	*pipe_pos;
	size_t		length;
	int			j;
	int			in_quotes;

	index = 0;
	start = 0;
	str_array = malloc((num_pipes + 2) * sizeof(char *));
	if (str_array == NULL)
		return (NULL);
	while (index <= num_pipes)
	{
		pipe_pos = input + start;
		in_quotes = 0;
		length = 0;
		while (pipe_pos[length] != '\0'
			&& (pipe_pos[length] != '|' || in_quotes))
		{
			if (pipe_pos[length] == '"')
				in_quotes = !in_quotes;
			length++;
		}
		str_array[index] = allocate_and_copy(input + start, length);
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
		start += length + 1;
		index++;
	}
	str_array[index] = NULL;
	return (str_array);
}

char	**split_string(const char *input)
{
	int	num_pipes;

	num_pipes = count_pipes(input);
	return (split_into_array(input, num_pipes));
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
		current = current->next;
	pipe_token = create_token("|", PIPE);
	current->next = pipe_token;
	current->next->next = head2;
	return (head1);
}
