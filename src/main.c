/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:19:47 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/02 16:09:45 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_readline(char **line)
{
    *line = readline("\033[32mminishell\033[0m$ ");

    if (*line == NULL)
    {
        perror("readline");
        exit(EXIT_FAILURE);
    }
    if (**line != '\0')
    {
        add_history(*line);
    }
}

// malloc l'environnement 
char **copy_env(char **original_env)
{
	int		len;
	int		i;
	char	**dup_env;

	i = 0;
	len = 0;

	while(original_env[len])
		len++;
	dup_env = malloc(sizeof(char *) * len + 1);
	if(!dup_env)
		free_and_error(NULL, NULL, "Copy_env: dup_env malloc error", 1);
	while(original_env[i])
	{
		dup_env[i] = strdup(original_env[i]);
		if(!dup_env[i])
			free_and_error(NULL, NULL, "Copy_env: dup_env dup error", 1);
		i++;
	}
	dup_env[i] = NULL;
	return(dup_env);
}

void init_shell(char *line, char ***envp)
{
	t_token *tokens;
	t_node *head;

	ft_readline(&line);
    tokens = lexer(line);
    head = parser(tokens);
    ft_expenser(head);
	exec(head, envp);
}

int main(int argc, char **argv, char **envp)
{
	char *line = NULL;
	char **env;
	
    if (argc > 2 && !*argv)
		return (0);
	env = copy_env(envp);
    while (1)
    {
		init_shell(line, &env);
    }
	//free
    return 0;
}
