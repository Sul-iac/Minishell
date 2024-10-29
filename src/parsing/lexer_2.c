/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:18:43 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/29 14:18:43 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

t_token_type	determine_type(char *token)
{
	if (strcmp(token, "|") == 0)
		return (PIPE);
	if (strncmp(token, ">>", 2) == 0)
		return (REDIR_APPEND);
	if (strncmp(token, ">", 1) == 0)
		return (REDIR_OUT);
	if (strncmp(token, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	if (strncmp(token, "<", 1) == 0)
		return (REDIR_IN);
	return (CMD);
}

void	skip_spaces(char **input)
{
	while (**input == ' ' || **input == '\t')
	{
		(*input)++;
	}
}

char	*extract_quoted_string(char **input)
{
	char	*start;
	char	quote_type;
	char	*end;
	size_t	len;
	char	*quoted_string;

	start = *input;
	quote_type = *start;
	end = start + 1;
	while (*end && *end != quote_type)
	{
		if (*end == '\\' && *(end + 1) == quote_type)
			end++;
		end++;
	}
	if (*end == quote_type)
	{
		len = end - start + 1;
		quoted_string = (char *)malloc(len + 1);
		strncpy(quoted_string, start, len);
		quoted_string[len] = '\0';
		*input = end + 1;
		return (quoted_string);
	}
	return (NULL);
}
