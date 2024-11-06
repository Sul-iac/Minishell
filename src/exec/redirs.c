/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:33:48 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/06 14:02:31 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int create_heredoc(const char *delimiter)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int temp_fd;

    temp_fd = open("/tmp/minishell_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (temp_fd == -1) {
        perror("create_heredoc: error creating temporary file");
        exit(EXIT_FAILURE);
    }
    while (1) {
        printf("> ");
        read = getline(&line, &len, stdin);
        if (read == -1)
		{
            perror("create_heredoc: error reading line");
            free(line);
            close(temp_fd);
            exit(EXIT_FAILURE);
        }
        line[strcspn(line, "\n")] = 0;
        if (strcmp(line, delimiter) == 0)
            break;
        dprintf(temp_fd, "%s\n", line);
    }
    free(line);
    close(temp_fd);
    temp_fd = open("/tmp/minishell_heredoc", O_RDONLY);
    if (temp_fd == -1)
	{
        perror("create_heredoc: error reopening temporary file");
        exit(EXIT_FAILURE);
    }
    return temp_fd;
}

void handle_redirections(t_node *cmd) 
{
    int fd;
	int here_doc;
    t_redirection *redir;

	here_doc = -1;
    redir = cmd->inputs;
    while (redir) 
	{
        if (redir->is_double)
		{
            here_doc = create_heredoc(redir->filename);
			fd = here_doc;
		}
		else
		{
            fd = open(redir->filename, O_RDONLY);
            if (fd == -1)
			{
                perror("open input redirection");
                exit(EXIT_FAILURE);
            }
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        redir = redir->next;
    }
    redir = cmd->outputs;
    while (redir)
	{
        if (redir->is_double)
            fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd == -1)
		{
            perror("open output redirection");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        redir = redir->next;
    }
	if(here_doc != -1)
		unlink("/tmp/minishell_heredoc");
}
