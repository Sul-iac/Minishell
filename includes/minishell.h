/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 14:46:14 by qbarron           #+#    #+#             */
/*   Updated: 2024/08/24 18:07:14 by qbarron          ###   ########.fr       */
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

// definis un type pour chaque token trouves
typedef struct s_token_type
{
    int type;
    const char *name;             //pour le debuggage
}             t_token_type;

t_token_type token_types[] = {
    {0, "COMMAND"},
    {1, "OPTION"},
    {2, "ARGUMENT"},
    {3, "OPERATOR"},
    {4, "PIPE"},
    {5, "INPUT_REDIRECTION"},
    {6, "OUTPUT_REDIRECTION"},
	{7, "APPENED_REDIRECTION"},
	{8, "HERE_DIRECTION"},
};

// definis une structures pour stocker les informations sur les tokens
typedef struct s_token
{
    t_token_type *type;
    char *value;
}              t_token;
//=========================
// main.c
void    ft_parsing(char *line, char **env);
void    ft_getline(char **line, size_t *len);

// exit.c
void    ft_exit(char *line);

// cd.c
void    ft_cd(char *args);

// echo.c
void    ft_echo(char *args);

// env.c
void    ft_env(char **env);

// pwd.c
void    ft_pwd(char *args);

// export.c
void    ft_export(char *args);

// unset.c
void    ft_unset(char *args);

# endif
