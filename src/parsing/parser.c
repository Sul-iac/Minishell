/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:47:01 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/28 15:47:01 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*create_node_parsing(t_node_type type, char *value)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	p if (value)
	{
		new_node->value = strdup(value);
		if (!new_node->value)
		{
			free(new_node);
			return (NULL);
		}
	}
	else
	{
		new_node->value = NULL;
	}
	new_node->next = NULL;
	new_node->inputs = NULL;
	new_node->outputs = NULL;
	new_node->builtin = false;
	new_node->is_last_cmd = false;
	return (new_node);
}

t_redirection	*create_redirection_parsing(char *filename, bool is_double)
{
	t_redirection	*new_redir;

	new_redir = (t_redirection *)malloc(sizeof(t_redirection));
	if (!new_redir)
		return (NULL);
	new_redir->filename = strdup(filename);
	new_redir->is_double = is_double;
	new_redir->next = NULL;
	return (new_redir);
}

void	append_redirection(t_redirection **head, t_redirection *new_redir)
{
	t_redirection	*temp;

	if (*head == NULL)
	{
		*head = new_redir;
	}
	else
	{
		temp = *head;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp->next = new_redir;
	}
}

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
			append_redirection(&inputs, create_redirection_parsing(tokens->value,
					tokens->type == REDIR_HEREDOC));
		}
		else if (tokens->type == REDIR_OUT || tokens->type == REDIR_APPEND)
		{
			append_redirection(&outputs, create_redirection_parsing(tokens->value,
					tokens->type == REDIR_APPEND));
		}
		tokens = tokens->next;
	}
	if (cmd_value)
	{
		node = create_node_parsing(CMD_2, cmd_value);
		node->inputs = inputs;
		node->outputs = outputs;
		free(cmd_value);
	}
	else
	{
		node = create_node_parsing(EMPTY_CMD, NULL);
		node->inputs = inputs;
		node->outputs = outputs;
	}
	return (node);
}

t_node	*convert_tokens_to_nodes(t_token *tokens)
{
	t_node	*node_head;
	t_node	*node_tail;
	t_token	*current_token;
	t_token	*cmd_tokens;
	t_node	*cmd_node;
	t_node	*pipe_node;
	t_node	*cmd_node;

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
				cmd_node = create_node_from_tokens(cmd_tokens);
				if (!node_head)
				{
					node_head = cmd_node;
					node_tail = cmd_node;
				}
				else
				{
					node_tail->next = cmd_node;
					node_tail = node_tail->next;
				}
				free_tokens(cmd_tokens);
				cmd_tokens = NULL;
			}
			pipe_node = create_node_parsing(PIPE_2, "|");
			node_tail->next = pipe_node;
			node_tail = pipe_node;
		}
		else
		{
			append_token(&cmd_tokens, create_token(current_token->value,
					current_token->type));
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

t_node	*parser(t_token *tokens)
{
	if (!tokens)
		return (NULL);
	t_node *head = convert_tokens_to_nodes(tokens);

	return (head);
}