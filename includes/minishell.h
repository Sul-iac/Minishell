#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <ctype.h>
# include <stddef.h>

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

typedef struct s_redirections
{
    char *filename;
    int type;
    struct s_redirection *next;
} t_redirections;

//=========================

// expenser.c
bool	ft_is_builtin(char *command);
void	mark_builtins(t_node *head);
void	ft_is_last_cmd(t_node *head);
static char	*get_env_variable_value(const char *input, size_t *i);
static char	*resize_result_if_needed(char *result, size_t *result_size, size_t required_size);

// expenser_2.c
char *process_input(const char *input, size_t *i, size_t *j, char *result, size_t *result_size);
char	*expand_env_variables(const char *input);
void	expand_node_values(t_node *head);
void	free_redirections(t_redirection *redir);
void	ft_expenser(t_node *head);

// free_nodes.c
void	free_nodes(t_node *head);

#endif
