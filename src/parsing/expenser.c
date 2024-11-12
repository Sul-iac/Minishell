/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expenser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:47:17 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/12 17:18:47 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_builtin(char *command)
{
	const char		*builtins[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit"};
	unsigned long	i;
	size_t			len;

	if (command == NULL)
		return (false);
	i = 0;
	while (i < 7)
	{
		len = ft_strlen(builtins[i]);
		if (ft_strncmp(command, builtins[i], len) == 0
			&& (command[len] == ' ' || command[len] == '\0'))
		{
			return (true);
		}
		i++;
	}
	return (false);
}

void	mark_builtins(t_node *head)
{
	t_node	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_is_builtin(current->value))
		{
			current->builtin = true;
		}
		else
		{
			current->builtin = false;
		}
		current = current->next;
	}
}

void	ft_is_last_cmd(t_node *head)
{
	t_node	*current;

	current = head;
	if (head == NULL)
	{
		return ;
	}
	while (current != NULL)
	{
		if (current->next == NULL)
		{
			current->is_last_cmd = 1;
		}
		else
		{
			current->is_last_cmd = 0;
		}
		current = current->next;
	}
}

void	ft_expenser(t_node *head)
{
	mark_builtins(head);
	ft_is_last_cmd(head);
	expand_node_values(head);
}
