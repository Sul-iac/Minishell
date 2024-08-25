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
#include <readline/readline.h>
#include <readline/history.h>


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
bool is_delimiter(char c);

//=========================
// main.c
void    ft_parsing(char *line, char **env);
void ft_readline(char **line);

// exit.c
void    ft_exit(char *line);

// cd.c
void ft_cd(int argc, char **argv, char **envp);

// echo.c
void ft_echo(int argc, char **argv, char **envp);

// env.c
void    ft_env(char **env);

// pwd.c
void    ft_pwd(char *args);

// export.c
void    ft_export(char *args);

// unset.c
void ft_unset(int argc, char **argv, char **envp);

//lexer.c


# endif
