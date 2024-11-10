/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:51:22 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/10 23:46:01 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	*init_pipe_execution(t_node *cmd, int *cmd_count)
{
	t_node	*tmp;
	pid_t	*pids;

	*cmd_count = 0;
	tmp = cmd;
	while (tmp)
	{
		if (tmp->type == CMD_2)
			(*cmd_count)++;
		tmp = tmp->next;
	}
	pids = malloc(sizeof(pid_t) * (*cmd_count));
	if (!pids)
		free_and_error(NULL, NULL, "Execute_pipes: malloc error", 1);
	return (pids);
}

void	handle_fork_error(pid_t *pids)
{
	free(pids);
	free_and_error(NULL, NULL, "Execute_pipes: fork error", 1);
}

t_pipe_data	*init_pipe_data(char ***env)
{
	t_pipe_data	*data;

	data = malloc(sizeof(t_pipe_data));
	if (!data)
		free_and_error(NULL, NULL, "malloc error", 1);
	data->in_fd = 0;
	data->cmd_index = 0;
	data->pids = NULL;
	data->env = env;
	return (data);
}

void	process_command(t_node *cmd, t_pipe_data *data)
{
	int		fd[2];
	pid_t	pid;

	handle_pipe_creation(cmd, fd);
	pid = fork();
	if (pid == -1)
		handle_fork_error(data->pids);
	if (pid == 0)
		child_process(cmd, data->env, data->in_fd, fd);
	else
	{
		data->pids[data->cmd_index++] = pid;
		parent_process(&data->in_fd, fd);
	}
}

void	wait_all_processes(t_pipe_data *data, int cmd_count)
{
	int	i;

	i = -1;
	while (++i < cmd_count)
		waitpid(data->pids[i], NULL, 0);
	if (data->in_fd != 0)
		close(data->in_fd);
	free(data->pids);
	free(data);
}
