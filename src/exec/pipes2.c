/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:51:22 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/10 18:31:15 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t    *init_pipe_execution(t_node *cmd, int *cmd_count)
{
    t_node  *tmp;
    pid_t   *pids;

    *cmd_count = 0;
    tmp = cmd;
    while (tmp)
    {
        if (tmp->type == CMD_2)
            (*cmd_count)++;
        tmp = tmp->next;
    }
    pids = malloc(sizeof(pid_t) * (*cmd_count));
    if (!pids)
        free_and_error(NULL, NULL, "Execute_pipes: malloc error", 1);
    return (pids);
}

void handle_fork_error(pid_t *pids)
{
    free(pids);
    free_and_error(NULL, NULL, "Execute_pipes: fork error", 1);
}

void wait_all_processes(pid_t *pids, int cmd_count, int in_fd)
{
    int i;

    for (i = 0; i < cmd_count; i++)
        waitpid(pids[i], NULL, 0);
    if (in_fd != 0)
        close(in_fd);
    free(pids);
}

void process_command(t_node *cmd, char ***env, int *in_fd, 
                        int *i, pid_t *pids)
{
    int     fd[2];
    pid_t   pid;

    handle_pipe_creation(cmd, fd);
    pid = fork();
    if (pid == -1)
        handle_fork_error(pids);
    if (pid == 0)
        child_process(cmd, env, *in_fd, fd);
    else
    {
        pids[(*i)++] = pid;
        parent_process(in_fd, fd);
    }
}
