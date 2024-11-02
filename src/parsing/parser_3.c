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
	t_token	*cmd_tokens;

	node_head = NULL;
	node_tail = NULL;
	cmd_tokens = NULL;
	while (tokens)
	{
		if (tokens->type == PIPE)
		{
			node_tail = process_command_tokens(&node_head,
					node_tail, cmd_tokens);
			cmd_tokens = NULL;
			node_tail = append_pipe_node(node_tail);
		}
		else
			append_token(&cmd_tokens,
				create_token(tokens->value, tokens->type));
		tokens = tokens->next;
	}
	if (cmd_tokens)
		node_tail = process_command_tokens(&node_head, node_tail, cmd_tokens);
	return (node_head);
}

t_node	*process_command_tokens(t_node **node_head,
	t_node *node_tail, t_token *cmd_tokens)
{
	t_node	*cmd_node;

	cmd_node = create_node_from_tokens(cmd_tokens);
	if (!(*node_head))
	{
		*node_head = cmd_node;
		node_tail = cmd_node;
	}
	else
	{
		node_tail->next = cmd_node;
		node_tail = cmd_node;
	}
	free_tokens(cmd_tokens);
	return (node_tail);
}

t_node	*append_pipe_node(t_node *node_tail)
{
	t_node	*pipe_node;

	pipe_node = create_node(PIPE_2, "|");
	if (node_tail)
		node_tail->next = pipe_node;
	return (pipe_node);
}
