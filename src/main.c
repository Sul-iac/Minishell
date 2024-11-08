/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:19:47 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/08 20:43:51 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **copy_env(char **original_env)
{
    int     len;
    int     i;
    char    **dup_env;

    i = 0;
    len = 0;
    while (original_env[len])
        len++;
    dup_env = malloc(sizeof(char *) * (len + 1));
    if(!dup_env)
        free_and_error(NULL, NULL, "Copy_env: dup_env malloc error", 1);
    while (original_env[i])
    {
        dup_env[i] = strdup(original_env[i]);
        if(!dup_env[i])
            free_and_error(NULL, NULL, "Copy_env: dup_env dup error", 1);
        i++;
    }
    dup_env[i] = NULL;
    return (dup_env);
}

char *ft_readline(void)
{
    char *line;

    line = readline("Minishell$ ");
    if (line && *line)
        add_history(line);
    return line;
}

void signal_handler(int signo)
{
    if (signo == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void init_parser_exec(char *line, t_main *main, char ***envp)
{
	char	**args;
    t_node	*head;
    t_token	*tokens;
	
	tokens = lexer(line);
    head = parser(tokens);
    ft_expenser(head);
	args = ft_split(head->value, ' ');
	if(!args)
		free_and_error(NULL, args, "init_parser_exec: error splitting arguments", 1);
    if (ft_strcmp(args[0], "exit") == 0)
	{
        main->is_running = ft_exit(args);	
	}
	else
		exec(head, envp);
    free(line);
}

void	init_shell(char ***envp, t_main *main)
{
    char	*line;

	main->is_running = 1;
    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
    while (main->is_running)
    {
        line = ft_readline();
        if (!line) 
		{
            main->is_running = 0;
			break;
        }
        if (*line)
			init_parser_exec(line, main, envp);
    }
}

int main(int argc, char **argv, char **envp)
{
    char **env;
	t_main main;
	
    if (argc > 2 && !*argv)
        return (0);
    using_history();
    env = copy_env(envp);
    init_shell(&env, &main);
	// free_everything(env, main);
    clear_history();
    return 0;
}
