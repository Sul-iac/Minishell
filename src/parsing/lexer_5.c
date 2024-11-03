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
	const char	*ptr = input;

	num_pipes = 0;
	while (*ptr != '\0')
	{
		if (*ptr == '|')
			num_pipes++;
		ptr++;
	}
	return (num_pipes);
}

char	*allocate_and_copy(const char *src, size_t length)
{
	char	*dest;

	dest = malloc(length + 1);
	if (dest)
	{
		strncpy(dest, src, length);
		dest[length] = '\0';
	}
	return (dest);
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
