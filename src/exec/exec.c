/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:51:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/12 14:30:27 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	restore_fds(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
}

static void	exec_pipe(t_node *cmd, char ***env, int fd_in, int fd_out)
{
	int	status;

	status = execute_pipes(cmd, env);
	if (status == 130)
		g_global_sig = 130;
	restore_fds(fd_in, fd_out);
}

static void	pre_exec_command(t_node *cmd, char ***env, int fd_in, int fd_out)
{
	if (cmd->builtin)
		execute_builtin(cmd, env);
	else
		execute_simple_command(cmd, env);
	restore_fds(fd_in, fd_out);
}

void	exec(t_node *cmd, char ***env)
{
	int		fd_in;
	int		fd_out;
	t_node	*current;

	current = cmd;
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	if (handle_redirections(cmd) == -1)
	{
		close(fd_in);
		close(fd_out);
		return ;
	}
	while (current && current->next)
	{
		if (current->next->type == PIPE_2)
		{
			exec_pipe(cmd, env, fd_in, fd_out);
			return ;
		}
		current = current->next;
	}
	pre_exec_command(cmd, env, fd_in, fd_out);
}
