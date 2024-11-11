/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:02:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/11 02:31:14 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 00:02:31 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/11 00:43:53 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*join_paths(char *dir, char *file)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(dir, "/.doom/");
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, file);
	if (ft_strcmp(file, "/.doom_ressources/DOOM1.WAD") == 0)
	{
		result = ft_strjoin(dir, file);
		return (result);
	}
	free(tmp);
	return (result);
}

static void	print_doom_art(void)
{
	printf("\033[2J\033[H");
	printf("\033[31m"
		"⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣀⣤⣴⣶⣶⣶⣦⣤⣀⡀\n"
		"⠀⠀⠀⠀⠀⢀⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⡀\n"
		"⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡀\n"
		" DOOM MODE ACTIVATED \n"
		"⠀ RIP AND TEAR !!!! \n"
		"\033[0m\n");
}

static void	setup_doom_args(char **args, char *exec_path, char *wad_path)
{
	args[0] = exec_path;
	args[1] = "-iwad";
	args[2] = wad_path;
	args[3] = NULL;
}

static void	free_doom_paths(char *exec_path, char *wad_path)
{
	if (exec_path)
		free(exec_path);
	if (wad_path)
		free(wad_path);
}

void	execute_utils(void)
{
	char	*current_dir;
	char	*exec_path;
	char	*wad_path;
	char	*args[4];

	current_dir = getcwd(NULL, 0);
	if (!current_dir)
		return ;
	exec_path = join_paths(current_dir, "doom_ascii/doom_ascii");
	wad_path = join_paths(current_dir, "/.doom_ressources/DOOM1.WAD");
	free(current_dir);
	if (!exec_path || !wad_path)
	{
		free_doom_paths(exec_path, wad_path);
		return ;
	}
	printf("exec_path: %s et wad_path: %s\n", exec_path, wad_path);
	if (access(exec_path, X_OK) == 0 && access(wad_path, R_OK) == 0)
	{
		print_doom_art();
		setup_doom_args(args, exec_path, wad_path);
		execv(exec_path, args);
	}
	free_doom_paths(exec_path, wad_path);
}
