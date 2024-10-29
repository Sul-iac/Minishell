/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:28:39 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/29 14:28:39 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*convert_tokens_to_nodes(t_token *tokens)
{
	t_node	*node_head;
	t_node	*node_tail;
	t_token	*current_token;
	t_token	*cmd_tokens;
	t_node	*cmd_node;
	t_node	*pipe_node;
	t_node	*cmd_noded;

	node_head = NULL;
	node_tail = NULL;
	current_token = tokens;
	cmd_tokens = NULL;
	while (current_token)
	{
		if (current_token->type == PIPE)
		{
			if (cmd_tokens)
			{
				cmd_noded = create_node_from_tokens(cmd_tokens);
				if (!node_head)
				{
					node_head = cmd_noded;
					node_tail = cmd_noded;
				}
				else
				{
					node_tail->next = cmd_noded;
					node_tail = node_tail->next;
				}
				free_tokens(cmd_tokens);
				cmd_tokens = NULL;
			}
			pipe_node = create_node(PIPE_2, "|");
			node_tail->next = pipe_node;
			node_tail = pipe_node;
		}
		else
		{
			append_token(&cmd_tokens,
				create_token(current_token->value, current_token->type));
		}
		current_token = current_token->next;
	}
	if (cmd_tokens)
	{
		cmd_node = create_node_from_tokens(cmd_tokens);
		if (!node_head)
		{
			node_head = cmd_node;
			node_tail = cmd_node;
		}
		else
		{
			node_tail->next = cmd_node;
		}
		free_tokens(cmd_tokens);
	}
	return (node_head);
}