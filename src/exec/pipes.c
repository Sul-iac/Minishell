/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:09:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/22 10:11:21 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void child_process(t_node *cmd, char **env, int *fd)
{
	pid_t pid;
	int in_fd = 0;

	while(cmd)
	{
		if(in_fd != 0)
		{
			dup2(in_fd, 0);
			close(in_fd);
		}
		if(in_fd == 0)
		{
			dup2(fd[1], 1);
			close(fd[1]);
		}
		parse_nbuiltin(cmd, env);
		exit(0);
	}
	else
	{
		wait
	}
}

void parent_process(t_node *cmd, char **env, int *fd)
{
	if()
}
