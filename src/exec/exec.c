/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:51:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/03 17:43:39 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int execute_command(t_node *cmd)
{
	t_shell_env context;
	int i = 0;
	//...
	if(cmd->builtin)
	{
		char *command = strdup(cmd->value);
		while(command[i] != ' ')
		{
			if(strcmp(command[i], "cd"))
			{
				ft_cd(command);
			}
			if(strcmp(command[i], "pwd"))
			{
				ft_pwd();
			}
			if(strcmp(command[i], "echo"))
			{
				ft_echo(command);
			}
		}
		cmd->builtin = 0;
	}
	if(cmd->next != NULL)
	{
		execute_pipe(cmd);
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
				execute_command(cmd);
			}
			current = current->next;
		}
	}
	return(0);
}

//==================================================================================//

t_node *create_node(t_token_type type, char *value, 
					t_redirection *inputs, t_redirection *outputs, 
					bool builtin, bool is_last_cmd)
{
	t_node *node = malloc(sizeof(t_node));
	node->type = type;
	node->value = strdup(value);
	node->inputs = NULL;
	node->outputs = NULL;
	node->builtin = builtin;
	node->is_last_cmd = is_last_cmd;
	node->next = NULL;
	return(node);
}

void exec_test()
{
	t_node *cmd1 = create_node(CMD, "cd", NULL, NULL, true, false);
	t_node *cmd2 = create_node(CMD, "..", NULL, NULL, true, true);
	cmd1->next = NULL;
	exec(cmd1);
}

int main(void)
{
	exec_test();
	return(0);
}