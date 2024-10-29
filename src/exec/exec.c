/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:51:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/29 18:37:34 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int execute_builtin(t_node *cmd, char **env)
{
    char **args;

	args = ft_split(cmd->value, ' ');
    if (!strcmp(args[0], "export") || !strcmp(args[0], "unset"))
         nforked_commands(cmd->value, env);
    if (!strcmp(args[0], "echo") || !strcmp(args[0], "env") || 
        !strcmp(args[0], "exit") || !strcmp(args[0], "pwd"))
        	forked_commands(args[0], env);
    return (1);
}

static int execute_command(t_node *cmd, char **env)
{
    int     len;
    char    **args;
    char    *path;
    char    *full_command;

    args = ft_split(cmd->value, ' ');
    if (!args)
        error();
    path = get_path(args[0], env);
    if (!path)
		error();
    len = strlen(path) + strlen(args[0]);
    full_command = malloc(sizeof(char) * (len + 1));
    if (!full_command)
		error();
    strcpy(full_command, path);
    full_command[len] = '\0';
    if (execve(full_command, args, env) == -1)
		error();
    return (0);
}

int execute_simple_command(t_node *cmd, char **env)
{
    pid_t   pid;
    int     status;
	char	**args;

    if (cmd->builtin)
	{
		args = ft_split(cmd->value, ' ');
		if(!args)
			error();
		int i = -1;
		// while(args[++i])
		// 	printf("execute_scommand: %s\n", args[i]);
		execute_builtin(cmd, env);
	}
    pid = fork();
    if (pid < 0)
		error();
    if (pid == 0)
    {
        execute_command(cmd, env);
        exit(EXIT_FAILURE);
    }
    else
        waitpid(pid, &status, 0);
    return (WEXITSTATUS(status));
}

int exec(t_node *cmd, char **env)
{
    char **args;
    int i;

    args = ft_split(cmd->value, ' ');
    if (!args)
        return (1);
	if(cmd->next != NULL)
		execute_pipes(cmd, env);
	else
	{
    	if (is_builtin(args[0]))
    	    env = nforked_commands(cmd->value, env);
    	else
		    execute_simple_command(cmd, env);
	}
	free(args);
    return (0);
}


//==================================================================================//

t_node	*create_node(int type, char *value, bool builtin)
{
	t_node *node = malloc(sizeof(t_node));
	node->type = type;
	node->value = strdup(value);
	node->builtin = builtin;
	node->next = NULL;
	return node;
}

t_redirections *create_redirection(char *filename, int type)
{
    t_redirections *redir = malloc(sizeof(t_redirections));
    if (!redir)
        return NULL;
    redir->filename = strdup(filename);
    redir->type = type;
    redir->next = NULL;
    return redir;
}

t_node *create_test_node(char *value, bool is_last)
{
    t_node *node = malloc(sizeof(t_node));
    if (!node)
        return NULL;

    node->type = CMD;  
    node->value = strdup(value);
    node->inputs = NULL;
    node->outputs = NULL;
    node->builtin = false;
    node->is_last_cmd = is_last;
    node->next = NULL;

    return node;
}

void free_redirections(t_redirection *redir)
{
    t_redirection *current;
    while (redir)
    {
        current = redir;
        redir = redir->next;
        free(current->filename);
        free(current);
    }
}

void free_command_list(t_node *cmd)
{
    t_node *current;
    while (cmd)
    {
        current = cmd;
        cmd = cmd->next;
        free(current->value);
        free_redirections(current->inputs);
        free_redirections(current->outputs);
        free(current);
    }
}

void test_execution(char **env)
{
    t_node *cmd;

    // printf("\n=== Test 1: Builtin (export) ===\n");
    // cmd = create_test_node("export TEST=test", true);
    // exec(cmd, env);
	// printf("done\n");
    // free_command_list(cmd);

    // printf("\n=== Test 2: Builtin (unset) ===\n");
    // cmd = create_test_node("unset TEST", true);
    // exec(cmd, env);
	// printf("done\n");
    // free_command_list(cmd);

	// printf("\n=== Test 2.5: Builtin (ls -l) ===\n");
    // cmd = create_test_node("ls -l", true);
    // exec(cmd, env);
	// printf("done\n");
    // free_command_list(cmd);

    // printf("\n=== Test 3: Pipeline (ls | grep a) ===\n");
    // cmd = create_test_node("ls", false);
    // cmd->next = create_test_node("grep a", true);
    // exec(cmd, env);
	// printf("done\n");
    // free_command_list(cmd);

    // printf("\n=== Test 4: Builtin avec redirection (echo hello > test.txt) ===\n");
    // cmd = create_test_node("echo hello", true);
    // cmd->outputs = create_redirection("test.txt", REDIR_OUT);
    // exec(cmd, env);
	// printf("done\n");

    // free_command_list(cmd);

    // printf("\n=== Test 5: Pipeline complexe (ls -l | grep a | wc -l) ===\n");
    // cmd = create_test_node("ls -l", false);
    // cmd->next = create_test_node("grep a", false);
    // cmd->next->next = create_test_node("wc -l", true);
    // exec(cmd, env);
	// printf("done\n");
    // free_command_list(cmd);
}

int execute_main(char **env)
{
    printf("=== Début des tests de minishell ===\n");
    test_execution(env);
    printf("\n=== Fin des tests ===\n");
    return 0;
}