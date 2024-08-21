#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>



//======================//
//          LEXER       //
//======================//

# define TOKEN_COMMAND      0
# define TOKEN_OPTIONS      1
# define TOKEN_ARGUMENTS    2
# define TOKEN_OPERATOR     3
# define MAX_ENTRIES        5

typedef struct  s_token
{
    char *command;
    int options_max;
    int arguments_max 
}               t_token;


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

#endif
