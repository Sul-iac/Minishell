/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:19:47 by qbarron           #+#    #+#             */
/*   Updated: 2024/08/21 20:57:25 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ft_getline(char **line, size_t *len)
{
    if (getline(line, len, stdin) == -1)
    {
        perror("getline");
        exit(EXIT_FAILURE);
    }
}

void    ft_parsing(char *line)
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
        ft_env(args);
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

int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len = 0;

    if (argc > 2 && !*argv)
		return (0);
    while (1)
    {
        printf("\033[32mminishell\033[0m$ ");
        ft_getline(&line, &len);
        ft_parsing(line);
    }
    return 0;
}
