/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:09:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/06 17:23:19 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_process(t_node *cmd, char ***env, int in_fd, int *fd)
{
	char *path;
	char **args;

	if(in_fd != 0)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if(cmd->next != NULL && cmd->next->type == PIPE_2)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
	}
	handle_redirections(cmd);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if(cmd->type == CMD_2)
	{
		if(is_builtin(cmd->value))
			execute_builtin(cmd, env);
		else
		{
			args = ft_split(cmd->value, ' ');
			if(!args || !args[0])
				free_and_error(NULL, args, "child_process: malloc error", 1);
			path = get_path(args[0], env);
			if(path)
			{
				if(execve(path, args, *env) == -1)
					free_and_error(NULL, NULL, "child_process: execve error", 1);
			}
			else
				free_and_error(NULL, NULL, "child_process: command not found", 1);
		}
	}
	exit(EXIT_SUCCESS);
}

void	parent_process(int *in_fd, int *fd, pid_t pid)
{
	close(fd[1]);
	if(*in_fd != 0)
		close(*in_fd);
	*in_fd = fd[0];
	waitpid(pid, NULL, 0);
}

void	execute_pipes(t_node *cmd, char ***env)
{
	pid_t	pid;
	int		fd[2];
	int		in_fd;

	in_fd = 0;
	while (cmd)
	{
		if(cmd->type == PIPE_2)
		{
			cmd = cmd->next;
			continue;
		}
		if(cmd->next && cmd->next->type == PIPE_2)
		{
			if(pipe(fd) == -1)
				free_and_error(NULL, NULL, "Execute_pipes: error creating pipe", 1);
		}
		pid = fork();
		if(pid == -1)
			free_and_error(NULL, NULL, "Execute_pipes: error creating new processus", 1);
		if(pid == 0)
			child_process(cmd, env, in_fd, fd);
		else
			parent_process(&in_fd, fd, pid);
		cmd = cmd->next;
	}
	if(in_fd != 0)
		close(in_fd);
}

char *get_path(char *cmd, char ***env)
{
	int			i;
	char		*path;
	char		**paths;
	char		*part_path;

	i = -1;
	while((*env)[++i] && ft_strnstr((*env)[i], "PATH=", 5) == 0);
	paths = ft_split((*env)[i] + 5, ':');
	if(!paths)
		free_and_error(NULL, paths, "Error while getting PATH to command", 1);
	i = -1;
	while(paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if(access(path, X_OK) == 0)
			return(path);
		free(path);
	}
	i = -1;
	while(paths[++i])
		free(paths[i]);
	free(paths);
	return(NULL);
}
