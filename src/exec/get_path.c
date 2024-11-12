/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 23:50:39 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/12 12:22:25 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*try_paths(char **paths, char *cmd)
{
	int		i;
	char	*path;
	char	*part_path;

	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

char	*get_path(char *cmd, char ***env)
{
	int		i;
	char	*path;
	char	**paths;

	i = -1;
	while ((*env)[++i] && ft_strnstr((*env)[i], "PATH=", 5) == 0)
		;
	paths = ft_split((*env)[i] + 5, ':');
	if (!paths)
		free_and_error(NULL, paths, "Error while getting PATH to command", 1);
	path = try_paths(paths, cmd);
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	return (path);
}
