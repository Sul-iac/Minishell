/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:52:42 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/30 15:17:32 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int redirect_output(t_redirection *redir) 
{
    int fd;
	
    if (redir->is_double)	// ">>"
        fd = open(redir->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else					// ">"
        fd = open(redir->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) 
	{
        perror("open output file");
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) < 0) 
	{
        perror("dup2 output");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

int redirect_input(t_redirection *redir) 
{
    int fd;
    if (redir->is_double) // "<<"
	{  
        char buffer[1024];
        char *temp_file = "/tmp/heredoc_temp";
        fd = open(temp_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) 
		{
            perror("open temp file");
            return -1;
        }
        printf("heredoc> ");
        while (fgets(buffer, 1024, stdin))
		{
            if (strncmp(buffer, redir->filename, strlen(redir->filename)) == 0)
                break;
            write(fd, buffer, strlen(buffer));
            printf("heredoc> ");
        }
        close(fd);
        fd = open(temp_file, O_RDONLY);
    }
	else					// "<"
        fd = open(redir->filename, O_RDONLY);
    if (fd < 0)
	{
        perror("open input file");
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) < 0)
	{
        perror("dup2 input");
        close(fd);
        return -1;
    }
    close(fd);
    return 0;
}

int apply_redirections(t_redirection *redirs) 
{
    t_redirection *current = redirs;
    while (current) 
	{
        if (current->is_double == 0)			// ">" ou "<"
		{ 
            if (strchr(current->filename, '>') != NULL)
			{
                if (redirect_output(current) < 0)
                    return -1;
            } else
			{
                if (redirect_input(current) < 0)
                    return -1;
            }
        } 
		else									// ">>" ou "<<"
		{
            if (strchr(current->filename, '>') != NULL)
                if (redirect_output(current) < 0)
                    return -1;
			else
                if (redirect_input(current) < 0)
                    return -1;
        }
        current = current->next;
    }
    return 0;
}





