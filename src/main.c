/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:19:47 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/06 17:47:02 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char **copy_env(char **original_env)
{
    int     len;
    int     i;
    char    **dup_env;

    i = 0;
    len = 0;
    while (original_env[len])
        len++;
    dup_env = malloc(sizeof(char *) * (len + 1));
    if(!dup_env)
        free_and_error(NULL, NULL, "Copy_env: dup_env malloc error", 1);
    while (original_env[i])
    {
        dup_env[i] = strdup(original_env[i]);
        if(!dup_env[i])
            free_and_error(NULL, NULL, "Copy_env: dup_env dup error", 1);
        i++;
    }
    dup_env[i] = NULL;
    return (dup_env);
}

char *ft_readline(void)
{
    char *user = getenv("USER");
    char *name = getenv("NAME");
    char cwd[1024];
    char prompt[2048];

    if (user == NULL)
        user = "user";
    if (name == NULL)
        name = "pc";
    if (getcwd(cwd, sizeof(cwd)) == NULL)
    {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    snprintf(prompt, sizeof(prompt), "\033[32m%s@%s:\033[0m\033[34m%s\033[0m $ ", user, name, cwd);
    return readline(prompt);
}

void signal_handler(int signo)
{
    if (signo == SIGINT)
    {
        write(1, "\n", 1);
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void init_shell(char ***envp)
{
    char *line;
    t_token *tokens;
    t_node *head;

    signal(SIGINT, signal_handler);
    signal(SIGQUIT, SIG_IGN);
    while (1)
    {
        signal(SIGINT, signal_handler);
        signal(SIGQUIT, SIG_IGN);
        line = ft_readline();
        if (!line)
            exit(0);
        if (*line)
        {
            tokens = lexer(line);
            head = parser(tokens);
            ft_expenser(head);
            signal(SIGINT, SIG_DFL);
            signal(SIGQUIT, SIG_DFL);
            exec(head, envp);
            free(line);
        }
    }
}

int main(int argc, char **argv, char **envp)
{
    char **env;

    if (argc > 2 && !*argv)
        return (0);
    using_history();
    env = copy_env(envp);
    init_shell(&env);
    clear_history();
    return 0;
}
