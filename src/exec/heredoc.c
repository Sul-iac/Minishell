/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:39:40 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/12 12:23:00 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	write_heredoc_line(int fd, char *line)
{
	if (*line != '\0')
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
	}
}

static int	process_heredoc_line(char *line, char *delimiter, int fd)
{
	if (!line)
	{
		if (g_global_sig == 130)
			return (1);
		write(1, "\n", 1);
		return (0);
	}
	if (ft_strcmp(line, delimiter) == 0)
	{
		free(line);
		return (1);
	}
	write_heredoc_line(fd, line);
	free(line);
	return (0);
}

void	handle_heredoc_input(int pipefd[2], char *delimiter)
{
	char	*line;
	int		should_break ;

	signal(SIGINT, handle_sigint_heredoc);
	should_break = 0;
	while (!should_break)
	{
		line = readline("> ");
		should_break = process_heredoc_line(line, delimiter, pipefd[1]);
		if(g_global_sig == 130)
			break ;
	}
	close(pipefd[1]);
	reset_signal();
}
