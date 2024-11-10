/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:09:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/10 23:54:33 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtin_nbuiltin(t_node *cmd, char ***env)
{
	char	*path;
	char	**args;

	if (cmd->builtin)
		execute_builtin(cmd, env);
	else
	{
		args = ft_split(cmd->value, ' ');
		if (!args || !args[0])
		{
			cleanup_cmd(cmd);
			free_and_error(NULL, args, "child_process: malloc error", 1);
		}
		path = get_path(args[0], env);
		if (path)
		{
			if (execve(path, args, *env) == -1)
			{
				cleanup_cmd(cmd);
				free_and_error(path, args, "child_process: execve error", 1);
			}
			free(path);
		}
		ft_free_array(args);
	}
}

void	child_process(t_node *cmd, char ***env, int in_fd, int *fd)
{
	if (in_fd != 0)
	{
		if (dup2(in_fd, 0) == -1)
		{
			cleanup_cmd(cmd);
			free_and_error(NULL, NULL, "child_process: dup2 error", 1);
		}
		close(in_fd);
	}
	if (cmd->next != NULL && cmd->next->type == PIPE_2)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
		{
			cleanup_cmd(cmd);
			free_and_error(NULL, NULL, "child_process: dup2 error", 1);
		}
		close(fd[1]);
	}
	handle_redirections(cmd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->type == CMD_2)
		execute_builtin_nbuiltin(cmd, env);
	exit(EXIT_SUCCESS);
}

void	parent_process(int *in_fd, int *fd)
{
	close(fd[1]);
	if (*in_fd != 0)
		close(*in_fd);
	*in_fd = fd[0];
}

void	handle_pipe_creation(t_node *cmd, int fd[2])
{
	if (cmd->next && cmd->next->type == PIPE_2)
	{
		if (pipe(fd) == -1)
			free_and_error(NULL, NULL, "Execute_pipes: error creating pipe", 1);
	}
}

void	execute_pipes(t_node *cmd, char ***env)
{
	t_pipe_data	*data;
	int			cmd_count;

	data = init_pipe_data(env);
	data->pids = init_pipe_execution(cmd, &cmd_count);
	while (cmd)
	{
		if (cmd->type == CMD_2)
			process_command(cmd, data);
		cmd = cmd->next;
	}
	wait_all_processes(data, cmd_count);
	return ;
}
