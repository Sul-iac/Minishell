/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:28:42 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/29 14:28:42 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_node_from_tokens(t_token *tokens)
{
	t_node			*node;
	t_redirection	*inputs;
	t_redirection	*outputs;
	char			*cmd_value;
	size_t			new_len;

	node = NULL;
	inputs = NULL;
	outputs = NULL;
	cmd_value = NULL;
	while (tokens)
	{
		if (tokens->type == CMD)
		{
			if (!cmd_value)
			{
				cmd_value = strdup(tokens->value);
			}
			else
			{
				new_len = strlen(cmd_value) + strlen(tokens->value) + 2;
				cmd_value = (char *)realloc(cmd_value, new_len);
				strcat(cmd_value, " ");
				strcat(cmd_value, tokens->value);
			}
		}
		else if (tokens->type == REDIR_IN || tokens->type == REDIR_HEREDOC)
		{
			append_redirection(&inputs, create_redirection(tokens->value,
					tokens->type == REDIR_HEREDOC));
		}
		else if (tokens->type == REDIR_OUT || tokens->type == REDIR_APPEND)
		{
			append_redirection(&outputs, create_redirection(tokens->value,
					tokens->type == REDIR_APPEND));
		}
		tokens = tokens->next;
	}
	if (cmd_value)
	{
		node = create_node(CMD_2, cmd_value);
		node->inputs = inputs;
		node->outputs = outputs;
		free(cmd_value);
	}
	else
	{
		node = create_node(EMPTY_CMD, NULL);
		node->inputs = inputs;
		node->outputs = outputs;
	}
	return (node);
}