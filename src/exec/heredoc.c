/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:39:40 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/12 14:30:01 by qbarron          ###   ########.fr       */
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

static int	process_heredoc_line(char *line, char *delimiter, int fd,
		int count_line)
{
	if (!line)
	{
		if (g_global_sig == 130)
		{
			g_global_sig = 0;
			return (1);
		}
		printf("minishell: warning: here-document on line %d ", count_line);
		printf("delimited by end-of-file (wanted `%s')\n", delimiter);
		return (1);
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
	int		count_line;
	int		should_break ;

	count_line = 0;
	signal(SIGINT, handle_sigint_heredoc);
	should_break = 0;
	while (!should_break)
	{
		line = readline("> ");
		should_break = process_heredoc_line(line, delimiter, pipefd[1],
				count_line);
		if (g_global_sig == 130)
		{
			close(pipefd[1]);
			reset_signal();
			return ;
		}
		if (!line)
			break ;
		count_line++;
	}
	close(pipefd[1]);
	reset_signal();
}
