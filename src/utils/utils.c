/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:32:57 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/17 15:41:52 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void error(void)
{
	perror("An error has occured\n");
	exit(EXIT_FAILURE);
}

// tokenise le chemin d'environnement 
char *get_path(char *cmd, char **env)
{
	int			i;
	char		*path;
	char		**paths;
	char		*part_path;

	i = 0;
	while(env[i] && ft_strnstr(env[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = -1;
	while(paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if(access(path, X_OK) == 0)
			return(path);
		free(path);
	}
	i = -1;
	while(paths[++i])
		free(paths[i]);
	free(paths);
	return(NULL);
}
void forked_commands(char *cmd)
{
	pid_t pid;
	if(pid < 0)
		error();
	if(pid == 0)
	{
		if(strcmp(cmd, "cd"))
			ft_cd(cmd);
		if(strcmp(cmd, "export"))
			ft_export(cmd);
		if(strcmp(cmd, "unset"))
			ft_unset(cmd);		
	}
}

void nforked_commands(char *cmd)
{
	
}