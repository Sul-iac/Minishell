/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:07:09 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/27 12:26:24 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_first_word(const char *str)
{
    int     i;
    char    *word;
    
    while (*str && (*str == ' ' || *str == '\t'))
        str++;
    i = 0;
    while (str[i] && str[i] != ' ' && str[i] != '\t')
        i++;
    word = malloc(sizeof(char) * (i + 1));
    if (!word)
        return (NULL);
    strncpy(word, str, i);
    word[i] = '\0';
    return (word);
}

bool	is_builtin(const char *cmd)
{
    return (!strcmp(cmd, "cd") || !strcmp(cmd, "export") || !strcmp(cmd, "unset") ||
            !strcmp(cmd, "echo") || !strcmp(cmd, "env") || !strcmp(cmd, "exit") ||
            !strcmp(cmd, "pwd"));
}

void	forked_commands(char *cmd, char **env)
{
	pid_t pid;
	printf("forked_command: %s\n", cmd);
	pid = fork();
	if(pid == -1)
		error();
	if(pid == 0)
	{
		if(strcmp(cmd, "echo") == 0)
			ft_echo(cmd);
		if(strcmp(cmd, "env") == 0)
			ft_env(env);
		if(strcmp(cmd, "exit") == 0)
			ft_exit(cmd);
		if(strcmp(cmd, "pwd") == 0)
			ft_pwd();
	}
	else if(pid > 0)
	{
		waitpid(pid, NULL, 0);
		exit(0);
	}
}

void	nforked_commands(char *cmd, char **env)
{
	char **args;
	
	args = ft_split(cmd, ' ');
	if(strcmp(args[0], "cd") == 0)
		ft_cd(args[1]);
	if(strcmp(cmd, "export") == 0)
		ft_export(cmd, env);
	if(strcmp(cmd, "unset") == 0)
		ft_unset(cmd);
}

void error(void)
{
	perror("Error");
	exit(EXIT_FAILURE);
}
