/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:19:47 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/03 11:24:36 by qbarron          ###   ########.fr       */
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

void    ft_parsing(char *line, char **env)
{
    line[strcspn(line, "\n")] = '\0';

    char *command = strtok(line, " ");
    char *args = strtok(NULL, "");

    if (command == NULL) {
        return;
    }
    if (strcmp(command, "cd") == 0)
        ft_cd(args);
    else if (strcmp(command, "echo") == 0)
        ft_echo(args);
    else if (strcmp(command, "env") == 0)
        ft_env(env);
    else if (strcmp(command, "export") == 0)
        ft_export(args);
    else if (strcmp(command, "pwd") == 0)
        ft_pwd(args);
    else if (strcmp(command, "unset") == 0)
        ft_unset(args);
    else if (strcmp(command, "exit") == 0)
        ft_exit(line);
    else
        printf("command not found: %s\n", command);
}

int main(int argc, char **argv, char **env)
{
    char *line = NULL;

    if (argc > 2 && !*argv)
		return (0); 
    while (1)
    {
        ft_readline(&line);
        ft_lexer(line);
        ft_parsing(line, env);
    }
    return 0;
}
