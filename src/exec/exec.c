/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 12:51:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/24 20:10:01 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int execute_builtin(t_node *cmd, char **env)
{
    char *command;

	command = cmd->value;
    if (!strcmp(command, "cd") || !strcmp(command, "export") || !strcmp(command, "unset"))
         nforked_commands(command, env);
    
    if (!strcmp(command, "echo") || !strcmp(command, "env") || 
        !strcmp(command, "exit") || !strcmp(command, "pwd"))
        	forked_commands(command, env);
    return (1);
}

static int execute_command(t_node *cmd, char **env)
{
    char    **args;
    char    *path;
    char    *full_command;
    int     len;

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

static int execute_simple_command(t_node *cmd, char **env)
{
    pid_t   pid;
    int     status;

    if (cmd->builtin)
        return (execute_builtin(cmd, env));

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
    char *first_word;
	first_word  = get_first_word(cmd->value);
    cmd->builtin = is_builtin(first_word);
    free(first_word);

    if (cmd->next == NULL)
        return (execute_simple_command(cmd, env));
    else
        return (execute_pipes(cmd, env));
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
    
    // printf("\n=== Test 1: Commande simple (ls -l) ===\n");
    // cmd = create_test_node("ls -l", true);
    // exec(cmd, env);
    // free_command_list(cmd);

    // printf("\n=== Test 2: Builtin (echo hello) ===\n");
    // cmd = create_test_node("echo hello", true);
    // exec(cmd, env);
    // free_command_list(cmd);

    // printf("\n=== Test 3: Pipeline (ls | grep a) ===\n");
    // cmd = create_test_node("ls", false);
    // cmd->next = create_test_node("grep a", true);
    // exec(cmd, env);
    // free_command_list(cmd);

    // printf("\n=== Test 4: Builtin avec redirection (echo hello > test.txt) ===\n");
    // cmd = create_test_node("echo hello", true);
    // cmd->outputs = create_redirection("test.txt", REDIR_OUT);  // Supposons que REDIR_OUT est défini
    // exec(cmd, env);
    // free_command_list(cmd);

    printf("\n=== Test 5: Pipeline complexe (ls -l | grep a | wc -l) ===\n");
    cmd = create_test_node("ls -l", false);
    cmd->next = create_test_node("grep a", false);
    cmd->next->next = create_test_node("wc -l", true);
    exec(cmd, env);
    free_command_list(cmd);
}

int execute_main(char **env)
{
    printf("=== Début des tests de minishell ===\n");
    test_execution(env);
    printf("\n=== Fin des tests ===\n");

    return 0;
}