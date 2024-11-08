/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:40:14 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/08 22:49:03 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parent_and_child(t_node *cmd, char ***env, int in_fd, int *fd)
{
	pid_t pid;

	pid = fork();
	if(pid == -1)
		free_and_error(NULL, NULL, "Execute_pipes: error creating new processus", 1);
	if(pid == 0)
		child_process(cmd, env, in_fd, fd);
	else
		parent_process(&in_fd, fd, pid);
	cmd = cmd->next;
}
