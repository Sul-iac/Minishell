/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:09:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/22 12:27:09 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void child_process(t_node *cmd, char **env, int in_fd, int *fd)
{
	if(in_fd != 0)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if(cmd->next != NULL)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	parse_nbuiltin(cmd, env);
	exit(0);
}

void parent_process(t_node *cmd, pid_t pid, int in_fd, int *fd)
{
	waitpid(pid, NULL, 0);
	if(in_fd != 0)
		close(in_fd);
	if(cmd->next != NULL)
	{
		close(fd[1]);
		in_fd = fd[0];
	}
}
