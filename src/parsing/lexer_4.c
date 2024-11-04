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

void	separate_tokens(t_token *current,
	t_token_list *cmd_list, t_token_list *other_list)
{
	t_token	*next;

	while (current)
	{
		next = current->next;
		current->next = NULL;
		if (current->type == CMD)
			add_token_to_list(&cmd_list->head, &cmd_list->tail, current);
		else
			add_token_to_list(&other_list->head, &other_list->tail, current);
		current = next;
	}
}

t_token	*reorganize_tokens(t_token *head)
{
	t_token_list	cmd_list;
	t_token_list	other_list;

	cmd_list.head = NULL;
	cmd_list.tail = NULL;
	other_list.head = NULL;
	other_list.tail = NULL;
	separate_tokens(head, &cmd_list, &other_list);
	if (cmd_list.tail)
		cmd_list.tail->next = other_list.head;
	if (cmd_list.head)
		return (cmd_list.head);
	else
		return (other_list.head);
}
