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

t_node	*create_node(t_node_type type, char *value)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	if (value)
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

t_redirection	*create_redirection(char *filename, bool is_double)
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

t_node	*parser(t_token *tokens)
{
	t_node	*head;

	if (!tokens)
		return (NULL);
	head = convert_tokens_to_nodes(tokens);
	return (head);
}
