/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expenser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:47:17 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/28 16:36:42 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	ft_is_builtin(char *command)
{
	const char		*builtins[] = {"echo ", "cd ", "pwd ", "export ",
		"unset ", "env ", "exit "};
	unsigned long	i;

	i = 0;
	if (command == NULL)
		return (false);
	while (i < 7)
	{
		if (strstr(command, builtins[i]) != NULL)
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
