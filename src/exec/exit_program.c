/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:24:21 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/12 12:01:39 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_program(t_node *head, char *line, t_main *main, char ***envp)
{
	char	**args;

	if (!head || !head->value)
	{
		free(line);
		return ;
	}
	args = ft_split(head->value, ' ');
	if (!args || !args[0])
	{
		free(line);
		if (args)
			free(args);
		return ;
	}
	if (ft_strcmp(args[0], "exit") == 0)
		main->is_running = ft_exit(args);
	else
	{
		exec(head, envp);
	}
	ft_free_array(args);
	free(line);
}
