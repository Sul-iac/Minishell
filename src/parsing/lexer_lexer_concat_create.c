/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_lexer_concat_create.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:33:00 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/12 17:00:04 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	skip_spaces(char **input)
{
	while (**input == ' ' || **input == '\t')
	{
		(*input)++;
	}
}

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (*head == NULL)
	{
		*head = new_token;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_token;
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
		current = current->next;
	pipe_token = create_token("|", PIPE);
	current->next = pipe_token;
	current->next->next = head2;
	return (head1);
}

t_token	*lexer(char *input)
{
	char	**str;
	t_token	*tokens;
	t_token	*final_tokens;
	int		j;

	str = split_string(input);
	final_tokens = NULL;
	j = 0;
	while (str[j])
	{
		tokens = tokenize_string(str[j]);
		if (tokens)
		{
			tokens = reorganize_tokens(tokens);
			tokens = group_cmd_tokens(tokens);
			final_tokens = concat_tokens(final_tokens, tokens);
		}
		j++;
	}
	free_split_array(str);
	return (final_tokens);
}
