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

t_token *process_command_token(char **ptr, t_token **head)
{
    char *debut = *ptr;
    while (**ptr && **ptr != ' ' && **ptr != '\t' && **ptr != '|' && **ptr != '<' && **ptr != '>')
    {
        (*ptr)++;
    }
    size_t lenlen = *ptr - debut;
    char *cmd_token = (char *)malloc(lenlen + 1);
    strncpy(cmd_token, debut, lenlen);
    cmd_token[lenlen] = '\0';
    append_token(head, create_token(cmd_token, CMD));
    free(cmd_token);
    return *head;
}

t_token	*reorganize_tokens(t_token *head)
{
	t_token	*cmd_head;
	t_token	*cmd_tail;
	t_token	*other_head;
	t_token	*other_tail;
	t_token	*next;
	t_token	*current;

	cmd_head = NULL;
	cmd_tail = NULL;
	other_head = NULL;
	other_tail = NULL;
	current = head;
	while (current)
	{
		next = current->next;
		current->next = NULL;
		if (current->type == CMD)
		{
			if (!cmd_head)
			{
				cmd_head = current;
				cmd_tail = current;
			}
			else
			{
				cmd_tail->next = current;
				cmd_tail = cmd_tail->next;
			}
		}
		else
		{
			if (!other_head)
			{
				other_head = current;
				other_tail = current;
			}
			else
			{
				other_tail->next = current;
				other_tail = other_tail->next;
			}
		}
		current = next;
	}
	if (cmd_tail)
		cmd_tail->next = other_head;
	if (cmd_head)
		return (cmd_head);
	else
		return (other_head);
}
