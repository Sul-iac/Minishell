/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:51:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/03 12:33:54 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int execute_command(t_node *cmd)
{
	//...
	if(cmd->builtin == 0)
	{
		char *command = strdup(cmd->value);
		printf("%s", command);
	}
	if(cmd->next != NULL)
	{
		execute_pipe;
	}
}

int execute_pipe(t_node *cmd)
{
	int fd[2];
	
	pid_t pid;
	if(pipe(fd) == -1)
		error();
	if(pid == 0)
		child_process(cmd, fd);
	parent_process(cmd, fd);
}

int exec(t_node *cmd)
{
	t_node *current = cmd;
	pid_t pid;

	pid = fork();
	if(pid < 0)
		error();
	if(pid == 0)
	{
		while(current)
		{
			if(current->type == CMD)
			{
				exec_command();
			}
			current = current->next;
		}
	}
}
