/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:09:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/08 23:41:52 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execute_builtin_nbuiltin(t_node *cmd, char ***env)
{
	char *path;
	char **args;
	
	if(cmd->builtin)
		execute_builtin(cmd, env);
	else
	{
		args = ft_split(cmd->value, ' ');
		if(!args || !args[0])
		{
			cleanup_cmd(cmd);
			free_and_error(NULL, args, "child_process: malloc error", 1);
		}
		path = get_path(args[0], env);
		if(path)
		{
			if(execve(path, args, *env) == -1)
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
	if(in_fd != 0)
	{
		if(dup2(in_fd, 0) == -1)
		{
			cleanup_cmd(cmd);
			free_and_error(NULL, NULL, "child_process: dup2 error", 1);
		}
		close(in_fd);
	}
	if(cmd->next != NULL && cmd->next->type == PIPE_2)
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
	if(cmd->type == CMD_2)
		execute_builtin_nbuiltin(cmd, env);
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

void	handle_pipe_creation(t_node *cmd, int fd[2])
{
    if (cmd->next && cmd->next->type == PIPE_2)
    {
        if (pipe(fd) == -1)
            free_and_error(NULL, NULL, "Execute_pipes: error creating pipe", 1);
    }
}

void    execute_pipes(t_node *cmd, char ***env)
{
    pid_t   pid;
    int     fd[2];
    int     in_fd;

    in_fd = 0;
    while (cmd)
    {
        if (cmd->type == PIPE_2)
        {
            cmd = cmd->next;
            continue;
        }
        handle_pipe_creation(cmd, fd);
        pid = fork();
        if (pid == -1)
            free_and_error(NULL, NULL, "Execute_pipes: error creating new processus", 1);
        if (pid == 0)
            child_process(cmd, env, in_fd, fd);
        else
            parent_process(&in_fd, fd, pid);
        cmd = cmd->next;
    }
    if (in_fd != 0)
		close(in_fd);
}
