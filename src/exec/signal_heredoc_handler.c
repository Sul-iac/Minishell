/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc_handler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 23:55:50 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/09 00:06:03 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	handle_sigint_heredoc(int signum)
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

void	reset_signal(void)
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}