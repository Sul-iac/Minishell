/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:19:47 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/10 11:14:57 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int g_global_sig = 0;

char	*ft_readline(void)
{
	char *line;

	line = readline("Minishell$ ");
	if (line && *line)
		add_history(line);
	return line;
}

t_node *init_parser(char *line)
{
    t_token *tokens;
    t_node  *head;

    if (!line || !*line)
        return (NULL);
    tokens = lexer(line);
    if (!tokens)
        return (NULL);
    head = parser(tokens);
    if (!head)
        return (NULL);
    ft_expenser(head);
    return (head);
}

void    exit_program(t_node *head, char *line, t_main *main, char ***envp)
{
    char    **args;

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
        exec(head, envp);
    free(line);
}

void    init_parser_exec(char *line, t_main *main, char ***envp)
{
    t_node  *head;

    head = init_parser(line);
    if (!head)
    {
        free(line);
        return ;
    }
    exit_program(head, line, main, envp);
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
			break ;
		}
		if (*line)
			init_parser_exec(line, main, envp);
	}
}

int	main(int argc, char **argv, char **envp)
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
