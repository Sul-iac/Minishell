/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:51:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/11 02:32:09 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_node *cmd, char ***env)
{
	char	**args;

	if (!cmd->value)
		free_and_error(NULL, NULL, "execute_builtin error: cmd not found", 1);
	args = ft_split(cmd->value, ' ');
	if (!args)
		free_and_error(NULL, NULL, "execute_builtin: error splitting arguments",
			1);
	if (!ft_strcmp(args[0], "export") || !ft_strcmp(args[0], "unset")
		|| !ft_strcmp(args[0], "cd"))
		nforked_commands(cmd->value, env);
	else if (!ft_strcmp(args[0], "echo") || !ft_strcmp(args[0], "env")
		|| !ft_strcmp(args[0], "pwd"))
		forked_commands(cmd->value, env);
	free(args);
	return (1);
}

void	execute_relative_absolute(char *cmd, char **args, char ***envp)
{
	if (cmd[0] == '/' || (cmd[0] == '.' && (cmd[1] == '/' || cmd[1] == '.')))
	{
		if (access(cmd, X_OK) == 0)
		{
			if (execve(cmd, args, *envp) == -1)
			{
				free_triple_pointer(envp);
				free_and_error(cmd, args, "error executing ./minishell", 1);
			}
		}
	}
}


int	execute_simple_command(t_node *cmd, char ***env)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		free_and_error(NULL, NULL,
			"Execute_simple_command: error creating new process", 1);
	if (pid == 0)
	{
		execute_command(cmd, env);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

void	exec(t_node *cmd, char ***env)
{
	int		fd_in;
	int		fd_out;
	t_node	*current;

	current = cmd;
	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	handle_redirections(cmd);
	while (current && current->next)
	{
		if (current->next->type == PIPE_2)
		{
			execute_pipes(cmd, env);
			return ;
		}
	}
	if (cmd->builtin)
		execute_builtin(cmd, env);
	else
		execute_simple_command(cmd, env);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
}
