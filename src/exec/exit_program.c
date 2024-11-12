/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:24:21 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/12 14:07:39 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_all_child_process(int *fd, t_node *cmd, char ***env)
{
	if (fd[0] != -1)
		close(fd[0]);
	if (fd[1] != -1)
		close(fd[1]);
	if (handle_redirections(cmd) == -1)
		return ;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (cmd->type == CMD_2)
		execute_builtin_nbuiltin(cmd, env);
}

void	exit_program(t_node *head, char *line, t_main *main, char ***envp)
{
	char	**args;

	if (!head || !head->value)
	{
		free(line);
		return ;
	}
	args = ft_split(head->value, ' ');
	if (!args || !args[0])
	{
		free(line);
		if (args)
			free(args);
		return ;
	}
	if (ft_strcmp(args[0], "exit") == 0)
		main->is_running = ft_exit(args);
	else
	{
		exec(head, envp);
	}
	ft_free_array(args);
	free(line);
}
