/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_prompt2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 19:24:21 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/11 02:06:30 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_get_dirname(void)
{
	char	*cwd;
	char	*last_slash;
	char	*dir_name;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_strdup("unknown"));
	last_slash = ft_strrchr(cwd, '/');
	if (last_slash && last_slash != cwd)
	{
		dir_name = ft_strdup(last_slash + 1);
		free(cwd);
		return (dir_name);
	}
	return (cwd);
}

void	exit_program(t_node *head, char *line, t_main *main, char ***envp)
{
	char	**args;

	if (!head || !head->value)
	{
		free(line);
		return ;
	}
	args = ft_split(head->value, ' ');
	if (!args || !args[0])
	{
		free(line);
		if (args)
			free(args);
		return ;
	}
	if (ft_strcmp(args[0], "exit") == 0)
		main->is_running = ft_exit(args);
	else
	{
		exec(head, envp);
	}
	ft_free_array(args);
	free(line);
}
