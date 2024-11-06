/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:24:34 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/06 17:50:40 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int g_global_sig = 0;

int handle_input_redirection(const char *file)
{
    int fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("Erreur d'ouverture du fichier d'entrée");
        return -1;
    }
    if (dup2(fd, STDIN_FILENO) == -1)
    {
        close(fd);
        perror("Erreur lors de la redirection de l'entrée standard");
        return -1;
    }
    close(fd);
    return 0;
}

int handle_output_redirection(const char *file, int flags)
{
    int fd = open(file, O_WRONLY | O_CREAT | flags, 0644);
    if (fd == -1)
    {
        perror("Erreur d'ouverture du fichier de sortie");
        return -1;
    }
    if (dup2(fd, STDOUT_FILENO) == -1)
    {
        close(fd);
        perror("Erreur lors de la redirection de la sortie standard");
        return -1;
    }
    close(fd);
    return 0;
}

void handle_heredoc_input(int pipefd[2], char *delimiter)
{
    char *line;

    signal(SIGINT, handle_sigint_heredoc);
    while (1)
    {
        line = readline("> ");
        if (!line)
        {
            if (g_global_sig == 130)
                break;
            write(1, "\n", 1);
        }
        else if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break;
        }
        else if (*line != '\0')
        {
            write(pipefd[1], line, strlen(line));
            write(pipefd[1], "\n", 1);
        }
        free(line);
    }
    close(pipefd[1]);
	reset_signal();
}

int handle_heredoc(char *delimiter)
{
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return -1;
    }
    handle_heredoc_input(pipefd, delimiter);
    close(pipefd[1]);
    return pipefd[0];
}

void handle_redirections(t_node *cmd)
{
    int				fd;
    t_redirection	*current;

    current = cmd->inputs;
    while (current)
    {
        if (current->is_double) // (<<)
        {
			fd = handle_heredoc(current->filename);
            if (fd == -1)
            {
                close(fd);
                return;
            }
            dup2(fd, STDIN_FILENO);
            close(fd); 
        }
        else // (<)
        {
            if (handle_input_redirection(current->filename) == -1)
                return;
        }
        current = current->next;
    }
    current = cmd->outputs;
    while (current)
    {
        if (current->is_double) // (>>)
        {
            if (handle_output_redirection(current->filename, O_APPEND) == -1)
                return;
        }
        else					// (>)
        {
            if (handle_output_redirection(current->filename, O_TRUNC) == -1)
                return;
        }
        current = current->next;
    }
}

void handle_sigint_heredoc(int signum)
{
    if (signum == SIGINT)
    {
        write(STDOUT_FILENO, "\n", 1);
        close(STDIN_FILENO);
        g_global_sig = 130;
    }
    else if (signum == SIGQUIT)
    {
        write(STDOUT_FILENO, "Quit (core dumped)\n", 18);
        exit(131);
    }
}

void reset_signal(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}