/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:51:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/09/30 13:52:02 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

typedef struct s_cmd
{
	char **args;
	t_cmd *next;
}				t_cmd;

typedef struct s_pipe
{
	int *front;
	int *rear;
	t_pipe *next;
}				t_pipe;




int exec(t_cmd* cmd_list, char **envp)
{
	t_cmd* current = cmd_list;
	int pid;
	while(current)
	{
		if(strcmp(current->args[1], "|"))
		pid = fork();
		if(pid == -1)
		{
			printf("Fork error");
			return(1);
		}
		else if(pid == 1)
		{
			if(execve(current->args[0], current->args, envp) == -1)
			{
				printf("Execve error");
				return(1);
			}
		}
		else
		{
			wait(NULL);
		}
		current->next;
	}
}