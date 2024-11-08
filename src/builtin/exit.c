/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:09:05 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/08 17:59:32 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_number(const char *str) {
    int i = 0;

    if (str[0] == '-')
        i++;
    while (str[i] != '\0')
	{
        if (!isdigit(str[i]))
            return 0;
        i++;
    }
    return 1;
}

int ft_exit(char *args, int *is_running) {
    char **args_res;

    args_res = ft_split(args, ' ');
    if (!args_res)
	{
        printf("exit: error while splitting arguments\n");
        *is_running = 0;
        return (1);
    }
    if (args_res[1])
	{
        if (!is_number(args_res[1]))
		{
            printf("exit: %s: numeric argument required\n", args_res[1]);
            *is_running = 0;
            return 1;
        }
        if (args_res[2] != NULL)
		{
            printf("exit: too many arguments\n");
            free(args_res);
            return 1;
        }
        *is_running = 0;
        free(args_res);
        return atoi(args_res[1]);
	}
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    printf("exit\n");
    *is_running = 0;
    free(args_res);
    return 0;
}
