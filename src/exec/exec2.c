/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 02:32:15 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/11 02:32:32 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	try_execute_command(char **args, char ***env)
{
	char	*path;
	char	*full_command;
	int		len;

	path = get_path(args[0], env);
	if (!path)
	{
		printf("minishell: %s: command not found\n", args[0]);
		exit(EXIT_FAILURE);
	}
	len = ft_strlen(path) + ft_strlen(args[0]);
	full_command = malloc(sizeof(char) * (len + 1));
	if (!full_command)
		free_and_error(full_command, NULL, "minishell: malloc error", 1);
	ft_strcpy(full_command, path);
	if (execve(full_command, args, *env) == -1)
		free_and_error(NULL, NULL, "minishell: execve error", 1);
	free(full_command);
}

static int	check_hell_command(char **args)
{
	if (ft_strcmp(args[0], "666") == 0)
	{
		ft_free_array(args);
		execute_utils();
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	execute_command(t_node *cmd, char ***env)
{
	char	**args;

	args = ft_split(cmd->value, ' ');
	if (!args)
		free_and_error(NULL, args, "minishell: args malloc error", 1);
	if (check_hell_command(args))
		return (1);
	execute_relative_absolute(cmd->value, args, env);
	try_execute_command(args, env);
	exit(EXIT_SUCCESS);
}