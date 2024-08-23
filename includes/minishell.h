/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:46:14 by qbarron           #+#    #+#             */
/*   Updated: 2024/08/23 15:56:51 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include "../src/libft/libft.h"
//======================//
//          LEXER       //
//======================//

# define OPTIONS_MAX        1

typedef struct  commande_infos
{
    char *command;
    int options_max;
    int arguments_max;
    char *valid_options[OPTIONS_MAX];
}               commande_infos;

typedef struct s_token
{
    char *command;
    int TOKEN_COMMAND;
    int TOKEN_ARGUMENTS;
    int TOKEN_OPERATORS;
    int TOKEN_OPTIONS;
}               t_token;

//=========================
// utils.c
//=========================
int ft_strcmp(char *s1, char *s2);




//=========================
// main.c
void    ft_parsing(char *line);
void    ft_getline(char **line, size_t *len);

// exit.c
void    ft_exit(char *line);

// cd.c
void    ft_cd(char *args);

// echo.c
void    ft_echo(char *args);

// env.c
void    ft_env(char *args);

// pwd.c
void    ft_pwd(char *args);

// export.c
void    ft_export(char *args);

// unset.c
void    ft_unset(char *args);

# endif
