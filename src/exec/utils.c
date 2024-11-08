/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:07:09 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/08 17:21:22 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_first_word(const char *str)
{
    int     i;
    char    *word;

	if(!*str || !str)
		return(NULL);
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

void	forked_commands(char *cmd, char ***env)
{
	pid_t pid;
	char **args;

	pid = fork();
	if(pid == -1)
		free_and_error(NULL, NULL, "Forked_commands: error creating new process", 1);
	if(pid == 0)
	{
		args = ft_split(cmd, ' ');
		if(!args)
			free_and_error(NULL, args, "Forked_command: error while splitting args", 1);
		if(strcmp(args[0], "echo") == 0)
			ft_echo(args);
		else if(strcmp(args[0], "env") == 0)
			ft_env(env);
		else if(strcmp(args[0], "pwd") == 0)
			ft_pwd();
		free_and_error(NULL, args, NULL, 0);
		exit(EXIT_SUCCESS);
	}
	else if(pid > 0)
		waitpid(pid, NULL, 0);
}

char **nforked_commands(char *cmd, char ***env)
{
	char **args;

	if(!cmd)
		free_and_error(cmd, NULL, "nforked_command: command not found", 1);
	args = ft_split(cmd, ' ');
	if(!args)
		free_and_error(NULL, args, "nforked_command: error while splitting arguments", 1);
	if(strcmp(args[0], "cd") == 0)
		ft_cd(args[1]);
	else if(strcmp(args[0], "export") == 0)
		*env = ft_export(args[1], env);
	else if(strcmp(args[0], "unset") == 0)
		*env = ft_unset(args[1], env);
	free_and_error(NULL, args, NULL, 0);
	return(*env);
}

