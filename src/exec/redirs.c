/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:34 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/10 23:48:21 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_output_redirection(const char *file, int flags)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | flags, 0644);
	if (fd == -1)
	{
		perror("Erreur d'ouverture du fichier de sortie");
		return (-1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		perror("Erreur lors de la redirection de la sortie standard");
		return (-1);
	}
	close(fd);
	return (0);
}

int	handle_heredoc_redirection(char *filename, int *fd)
{
	*fd = handle_heredoc(filename);
	if (*fd == -1)
	{
		close(*fd);
		return (-1);
	}
	if (dup2(*fd, STDIN_FILENO) == -1)
	{
		close(*fd);
		return (-1);
	}
	close(*fd);
	return (0);
}

int	handle_heredoc(char *delimiter)
{
	int	pipefd[2];

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	handle_heredoc_input(pipefd, delimiter);
	close(pipefd[1]);
	return (pipefd[0]);
}

void	handle_redirections(t_node *cmd)
{
	if (process_input_redirections(cmd->inputs) == -1)
		return ;
	if (process_output_redirections(cmd->outputs) == -1)
		return ;
}
