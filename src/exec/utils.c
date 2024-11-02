/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 12:07:09 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/02 16:07:52 by qbarron          ###   ########.fr       */
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

bool	is_builtin(const char *cmd)
{
    return (!strcmp(cmd, "cd") || !strcmp(cmd, "export") || !strcmp(cmd, "unset") ||
            !strcmp(cmd, "echo") || !strcmp(cmd, "env") || !strcmp(cmd, "exit") ||
            !strcmp(cmd, "pwd"));
}

void	forked_commands(char *cmd, char ***env)
{
	pid_t pid;
	pid = fork();
	if(pid == -1)
		free_and_error(NULL, NULL, "Forked_commands: error creating new process", 1);
	if(pid == 0)
	{
		if(strcmp(cmd, "echo") == 0)
			ft_echo(cmd);
		else if(strcmp(cmd, "env") == 0)
			ft_env(env);
		else if(strcmp(cmd, "exit") == 0)
			ft_exit(cmd);
		else if(strcmp(cmd, "pwd") == 0)
			ft_pwd();
		exit(EXIT_SUCCESS);
	}
	else if(pid > 0)
		waitpid(pid, NULL, 0);
}

char **nforked_commands(char *cmd, char ***env)
{
	char **args;

	if(!cmd)
	{
		perror("nforked_command: cmd not found");
		return(NULL);
	}
	args = ft_split(cmd, ' ');
	if(strcmp(args[0], "cd") == 0)
		ft_cd(args[1]);
	else if(strcmp(args[0], "export") == 0)
		*env = ft_export(args[1], env);	
	else if(strcmp(args[0], "unset") == 0)
		*env = ft_unset(args[1], env);
	return(*env);
}

