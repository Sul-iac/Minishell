#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <ctype.h>

typedef enum e_token_type {
    CMD,
    PIPE,
    REDIR_IN,
    REDIR_HEREDOC,
    REDIR_OUT,
    REDIR_APPEND
} t_token_type;

typedef struct s_token {
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

typedef enum e_node_type {
    CMD,
    PIPE,
    EMPTY_CMD
} t_node_type;

typedef struct redirection {
    char                *filename;
    bool                is_double; //0 <> 1 <<>>
    struct redirection  *next;
} t_redirection

typedef struct s_node {
    t_node_type     type;
    char            *value;
    struct s_node   *next;
    t_redirection   *inputs; //< et <<
    t_redirection   *outputs; // > et >>
    bool            builtin;
    bool            is_last_cmd;
} t_node;

//=========================
// main.c
void	ft_parsing(char *line);
void    ft_getline(char **line, size_t *len);

// lexer.c
t_token	*new_token(char *value, t_token_type type);
void	add_token(t_token **token_list, char *value, t_token_type type);
void lexer(char *input, t_token **token_list);

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
