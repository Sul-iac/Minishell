/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:09:46 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/25 22:19:30 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static bool check_n_flag(const char *str, int *i)
{
    if (str[*i] != '-')
        return (false);
    (*i)++;
    if (str[*i] != 'n')
        return (false);
    while (str[*i] == 'n')
        (*i)++;
    if (str[*i] == ' ' || str[*i] == '\0')
        return (true);
    *i -= 1;
    return (false);
}

static void print_char(char c, char next_c)
{
    if (c == '\\' && next_c)
    {
        if (next_c == 'n')
            write(1, "\n", 1);
        else if (next_c == 't')
            write(1, "\t", 1);
        else if (next_c == '\\')
            write(1, "\\", 1);
        else
        {
            write(1, &c, 1);
            write(1, &next_c, 1);
        }
    }
    else if (c != '\\' || !next_c)
        write(1, &c, 1);
}

int ft_echo(char *str)
{
    int     i;
    bool    n_flag;

    if (!str)
    {
        write(1, "\n", 1);
        return (0);
    }
    i = 0;
    n_flag = false;
    while (str[i] == ' ')
        i++;
    if (strncmp(str + i, "echo", 4) == 0)
        i += 4;
    while (str[i] == ' ')
        i++;
    while (str[i] && check_n_flag(str, &i))
    {
        n_flag = true;
        while (str[i] == ' ')
            i++;
    }
    while (str[i])
    {
        if (str[i] == '\\')
        {
            print_char(str[i], str[i + 1]);
            if (str[i + 1])
                i += 2;
            else
                i++;
        }
        else
        {
            print_char(str[i], '\0');
            i++;
        }
    }
    return (0);
}