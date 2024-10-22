/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:51:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/22 10:33:22 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	parse_builtin(t_node *cmd, char **env)
{
	char *commande = strdup(cmd->value);
	if(strcmp(commande, "cd") || strcmp(commande, "export") || strcmp(commande, "unset"))
	{
		nforked_commands(commande);
		cmd->builtin = 0;
	}
	if(strcmp(commande, "echo") || strcmp(commande, "env") || strcmp(commande, "exit")
								|| strcmp(commande, "pwd"))
	{
		forked_commands(commande);
		cmd->builtin = 0;
	}
}

int	execute_pipes(t_node *cmd, char **env)
{
	pid_t pid;
	int fd[2];
	int in_fd = 0;

	while(cmd)
	{
		if(cmd->next != NULL)
			if(pipe(fd) == -1)
				error();
		if((pid = fork()) == -1)
			error();
		else if(pid == 0)
		{
			if(in_fd != 0)
			{
				dup2(in_fd, 0);
				close(in_fd);
			}
			if(cmd->next != NULL)
			{
				dup2(fd[1], 1);
				close(fd[1]);
			}
			parse_nbuiltin(cmd, env);
			exit(0);
		}
		else
		{
			waitpid(pid, NULL, 0);
			if(in_fd != 0)
				close(in_fd);
			if(cmd->next != NULL)
			{
				close(fd[1]);
				in_fd = fd[0];
			}
		}
		cmd = cmd->next;
	}
	if(in_fd != 0)
		close(in_fd);
}

void	parse_nbuiltin(t_node *cmd, char **env)
{
	int i;
	int len;
	char *path;
	char **args;
	char *full_command;

	args = ft_split(cmd->value, ' ');
	path = get_path(args[0], env);
	if (!path)
		error();
	full_command = malloc(sizeof(char) * (strlen(path) + strlen(args[0]) + 1));
	if (!full_command)
		error();
	i = 0;
	strcpy(full_command, path);
	full_command[i] = '\0';
	pid_t pid = fork();
	if (pid == 0)
		if (execve(full_command, args, env) == -1)
			error();
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	else
		error();
	free(full_command);
}

int exec(t_node *cmd, char **env)
{
	t_node *current = cmd;
	pid_t pid;

	if(cmd->next == NULL)
	{
		if (cmd->builtin)
			parse_builtin(current, env);
		else
		{
			pid = fork();
			if (pid < 0)
				error();
			if (pid == 0)
				parse_nbuiltin(current, env);
			else if (pid > 0)
				waitpid(pid, NULL, 0);
		}
	}
	else
		execute_pipe(cmd, env);
	return (0);
}

//==================================================================================//

// t_node *create_node(t_token_type type, char *value,
// 					t_redirection *inputs, t_redirection *outputs,
// 					bool builtin, bool is_last_cmd)
// {
// 	t_node *node = malloc(sizeof(t_node));
// 	node->type = type;
// 	node->value = strdup(value);
// 	node->inputs = NULL;
// 	node->outputs = NULL;
// 	node->builtin = builtin;
// 	node->is_last_cmd = is_last_cmd;
// 	node->next = NULL;
// 	return(node);
// }

t_node	*create_node(int type, char *value, bool builtin)
{
	t_node *node = malloc(sizeof(t_node));
	node->type = type;
	node->value = strdup(value);
	node->builtin = builtin;
	node->next = NULL;
	return node;
}

// void print_command_list(t_node *cmd)
// {
//     t_node *current = cmd;

//     while (current != NULL)
//     {
//         printf("Commande: %s\n", current->value);
//         printf("Builtin: %s\n", current->builtin ? "Oui" : "Non");
//         printf("Derniere commande: %s\n", current->is_last_cmd ? "Oui" : "Non");

//         if (current->inputs)
//             printf("Redirection d'entree\n");
//         if (current->outputs)
//             printf("Redirection de sortie\n");

//         printf("\n");
//         current = current->next;
//     }
// }

void	exec_test(char **env)
{
	// t_node *cmd1 = create_node(CMD, "echo Bonjour ca va", NULL, NULL, false, false);
	// t_node *cmd1 = create_node(CMD, "grep Bonjour", NULL, NULL, false, true);
	t_node *cmd1 = create_node(CMD, "ls -l", false);
	cmd1->next = NULL;
	// print_command_list(cmd1);
	exec(cmd1, env);
}

int	execute_main(char **env)
{
	exec_test(env);
	return (0);
}