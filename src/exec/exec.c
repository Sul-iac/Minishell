/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:51:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/03 14:14:07 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


int execute_command(t_node *cmd)
{
	//...
	if(cmd->builtin)
	{
		char *command = strdup(cmd->value);
		if(strcmp(command, "cd"))
		{
			//exec_excve()
		}
		cmd->builtin = 0;
	}
	// else if(cmd->next != NULL)
	// {
	// 	execute_pipe(cmd);
	// }
}

// void	exec_excve(t_node *cmd, char )
// {
// 	// if(execve(path, cmd, envp) == -1)
// 	// 	error();
// }

// int execute_pipe(t_node *cmd)
// {
// 	int fd[2];
	
// 	pid_t pid;
// 	if(pipe(fd) == -1)
// 		error();
// 	if(pid == 0)
// 		child_process(cmd, fd);
// 	parent_process(cmd, fd);
// }

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
				printf("executing the command:\n");
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
	t_node *cmd1 = create_node(CMD, "echo", NULL, NULL, true, false);
	t_node *cmd2 = create_node(CMD, "-n Bonjour", NULL, NULL, true, true);
	cmd1->next = cmd2;
	exec(cmd1);
}

int main(void)
{
	exec_test();
	return(0);
}