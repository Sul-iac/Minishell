/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:24:56 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/29 14:24:56 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*process_command_token(char **ptr, t_token **head)
{
	char	*debut;
	size_t	lenlen;
	char	*cmd_token;

	debut = *ptr;
	while (**ptr && **ptr != ' ' && **ptr != '\t' && **ptr != '|'
		&& **ptr != '<' && **ptr != '>')
	{
		(*ptr)++;
	}
	lenlen = *ptr - debut;
	cmd_token = (char *)malloc(lenlen + 1);
	strncpy(cmd_token, debut, lenlen);
	cmd_token[lenlen] = '\0';
	append_token(head, create_token(cmd_token, CMD));
	free(cmd_token);
	return (*head);
}

t_token	*add_token_to_list(t_token **head, t_token **tail, t_token *token)
{
	if (!*head)
	{
		*head = token;
		*tail = token;
	}
	else
	{
		(*tail)->next = token;
		*tail = token;
	}
	return (token);
}

void	separate_tokens(t_token *current, t_token **cmd_head, t_token **cmd_tail, t_token **other_head, t_token **other_tail)
{
	t_token	*next;

	while (current)
	{
		next = current->next;
		current->next = NULL;
		if (current->type == CMD)
			add_token_to_list(cmd_head, cmd_tail, current);
		else
			add_token_to_list(other_head, other_tail, current);
		current = next;
	}
}

t_token	*reorganize_tokens(t_token *head)
{
	t_token	*cmd_head;
	t_token	*cmd_tail;
	t_token	*other_head;
	t_token	*other_tail;

	cmd_head = NULL;
	cmd_tail = NULL;
	other_head = NULL;
	other_tail = NULL;
	separate_tokens(head, &cmd_head, &cmd_tail, &other_head, &other_tail);
	if (cmd_tail)
		cmd_tail->next = other_head;
	if (cmd_head)
		return (cmd_head);
	else
		return (other_head);
}
