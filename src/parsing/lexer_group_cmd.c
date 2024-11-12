/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_group_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:34:21 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/12 14:34:21 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*group_consecutive_cmd_tokens(t_token **temp, size_t *grouped_len)
{
	char	*grouped_value;

	grouped_value = strdup((*temp)->value);
	*grouped_len = strlen(grouped_value);
	while ((*temp)->next && (*temp)->next->type == CMD)
	{
		*temp = (*temp)->next;
		*grouped_len += strlen((*temp)->value) + 1;
		grouped_value = (char *)realloc(grouped_value, *grouped_len + 1);
		strcat(grouped_value, " ");
		strcat(grouped_value, (*temp)->value);
	}
	return (grouped_value);
}

t_token	*group_cmd_tokens(t_token *head)
{
	t_token	*grouped_head;
	t_token	*temp;
	char	*grouped_value;
	size_t	grouped_len;
	t_token	*new_cmd_token;

	grouped_head = NULL;
	temp = head;
	while (temp)
	{
		if (temp->type == CMD)
		{
			grouped_value = group_consecutive_cmd_tokens(&temp, &grouped_len);
			new_cmd_token = create_token(grouped_value, CMD);
			append_token(&grouped_head, new_cmd_token);
			free(grouped_value);
		}
		else
			append_token(&grouped_head, create_token(temp->value, temp->type));
		temp = temp->next;
	}
	return (grouped_head);
}
