/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:19:47 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/12 18:16:54 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		g_global_sig = 0;

char	*ft_readline(void)
{
	char	*line;

	line = NULL;
	if (!line)
		line = readline("minishell$ ");
	else
	{
		if (g_global_sig == 130)
		{
			g_global_sig = 0;
			rl_reset_terminal(NULL);
		}
		line = readline(line);
		free(line);
	}
	if (line && *line)
		add_history(line);
	return (line);
}

t_node	*init_parser(char *line)
{
	t_token	*tokens;
	t_node	*head;

	if (!line || !*line)
		return (NULL);
	tokens = lexer(line);
	if (!tokens)
		return (NULL);
	head = parser(tokens);
	clean_tokens(tokens);
	if (!head)
		return (NULL);
	ft_expenser(head);
	return (head);
}

void	init_parser_exec(char *line, t_main *main, char ***envp)
{
	t_node	*head;

	head = init_parser(line);
	if (!head)
	{
		free(line);
		return ;
	}
	exit_program(head, line, main, envp);
	clean_nodes(head);
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
	char	**env;
	t_main	main;

	if (argc > 2 && !*argv)
		return (0);
	using_history();
	env = copy_env(envp);
	init_shell(&env, &main);
	clear_history();
	return (0);
}
