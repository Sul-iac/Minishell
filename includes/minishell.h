#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <ctype.h>
#include <stddef.h>

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
    CMD_2,
    PIPE_2,
    EMPTY_CMD // a voir pour si y'a juste une redir donc pas de value de node
} t_node_type;

typedef struct redirection {
    char                *filename; //penser a enlever les < > << >> dans le lexer pour mettre juste le nom
    bool                is_double; //0 <> 1 <<>>
    struct redirection  *next;
} t_redirection;

typedef struct s_node {
    t_node_type     type; // CMD ou PIPE par node ou EMPTY_CMD si pas de CMD entre deux pipe
    char            *value; //token CMD prend la valeur du token //attention si pas de cmd mais jsute redir //si pas de value alors CMD_2 to EMPTY_CMD
    struct s_node   *next; 
    t_redirection   *inputs; //< et <<
    t_redirection   *outputs; // > et >>
    bool            builtin; // mettre a 0/false pour le moment //expenser faire des strcmp faire attention a tous les cas de quote possible
    bool            is_last_cmd; // mettre a 0/false pour le moment //expenser juste a mettre sur la derniere commande
} t_node;

// expenser les variable d'environnement

//=========================
// main.c
void	ft_parsing(char *line);
void    ft_getline(char **line, size_t *len);

// lexer.c

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
