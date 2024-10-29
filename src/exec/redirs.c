/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:52:42 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/29 19:42:52 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void handle_redirections(t_node *cmd) 
{
    int fd;

    if (cmd->outputs != NULL) 
	{
        t_redirection *redir = cmd->outputs;
        while (redir) 
		{
            if (redir->is_double)
                fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			else
                fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd == -1)
			{
                perror("open output file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDOUT_FILENO); 
            close(fd);
            redir = redir->next;
        }
    }
    if (cmd->inputs != NULL) 
	{
        t_redirection *redir = cmd->inputs;

        while (redir)
		{
            fd = open(redir->filename, O_RDONLY);
            if (fd == -1)
			{
                perror("open input file");
                exit(EXIT_FAILURE);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
            redir = redir->next;
        }
    }
}


