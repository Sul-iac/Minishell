/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 11:32:57 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/03 18:31:17 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void error(void)
{
	perror("\033[31mAn error has occured");
	exit(EXIT_FAILURE);
}

// tokenise le chemin d'environnement 
char *get_path(char *cmd)
{
	int			i;
	char		*path;
	char		**paths;
	char		*part_path;
	char		**env;
	t_shell_env *envp;
	
	env = envp->env;
	i = 0;
	while(env[i] && strnstr(env[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(env[i] + 5, ':');
	i = 0;
	while(paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(paths[i], cmd);
		free(part_path);
		if(access(path, F_OK) == 0)
			return(path);
		free(path);
		i++;
	}
	i = -1;
	while(paths[++i])
		free(paths[i]);
	free(paths);
	return(NULL);
}