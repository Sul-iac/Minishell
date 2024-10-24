/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:09:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/24 23:24:47 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	child_process(t_node *cmd, char **env, int in_fd, int *fd)
{
	if (in_fd != 0)
	{
		dup2(in_fd, 0);
		close(in_fd);
	}
	if (cmd->next != NULL)
	{
		dup2(fd[1], 1);
		close(fd[1]);
	}
	is_builtin(cmd->value);
	exit(0);
}

void	parent_process(t_node *cmd, pid_t pid, int in_fd, int *fd)
{
	waitpid(pid, NULL, 0);
	if (in_fd != 0)
		close(in_fd);
	if (cmd->next != NULL)
	{
		close(fd[1]);
		in_fd = fd[0];
	}
}

int	execute_pipes(t_node *cmd, char **env)
{
	pid_t	pid;
	int		fd[2];
	int		in_fd;

	in_fd = 0;
	while (cmd)
	{
		if (cmd->next != NULL)
			if (pipe(fd) == -1)
				error();
		pid = fork();
		if (pid == -1)
			error();
		else if (pid == 0)
			child_process(cmd, env, in_fd, fd);
		else
			parent_process(cmd, pid, in_fd, fd);
		cmd = cmd->next;
		printf("Test pipes\n");
	}
	if (in_fd != 0)
		close(in_fd);
	return (0);
	
}

char *get_path(char *cmd, char **env)
{
	int			i;
	char		*path;
	char		**paths;
	char		*part_path;

	i = 0;
	while(env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while(paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(paths[i], cmd);
		free(part_path);
		if(access(path, F_OK) == 0)
			return(path);
		free(path);
		i++;
	}
	i = -1;
	while(paths[++i])
		free(paths[i]);
	free(paths);
	return(NULL);
}
