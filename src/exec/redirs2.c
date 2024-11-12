/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:53:37 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/12 12:56:01 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_input_redirection(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", file);
		return(-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		perror("Erreur lors de la redirection de l'entrée standard");
		return(-1);
	}
	close(fd);
	return (0);
}

int	process_input_redirections(t_redirection *current)
{
	int	fd;

	while (current)
	{
		if (current->is_double)
		{
			if (handle_heredoc_redirection(current->filename, &fd) == -1)
			{
				if(g_global_sig == 130)
					exit(130);
				return (-1);
			}
		}
		else
		{
			if (handle_input_redirection(current->filename) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

int	process_output_redirections(t_redirection *current)
{
	while (current)
	{
		if (current->is_double)
		{
			if (handle_output_redirection(current->filename, O_APPEND) == -1)
				return (-1);
		}
		else
		{
			if (handle_output_redirection(current->filename, O_TRUNC) == -1)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
