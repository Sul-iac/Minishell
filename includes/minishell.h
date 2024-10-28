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
// main.c
void ft_readline(char **line);
char **copy_env(char **original_env);
void init_shell(char *line, char **envp);

// lexer.c
t_token *create_token(char *value, t_token_type type);
void append_token(t_token **head, t_token *new_token);
t_token_type determine_type(char *token);
void skip_spaces(char **input);
char *extract_quoted_string(char **input);
t_token *tokenize_string(char *input);
t_token *reorganize_tokens(t_token *head);
char **split_string(const char *input);
void free_tokens(t_token *head);
void free_split_array(char **array);
t_token *concat_tokens(t_token *head1, t_token *head2);
t_token *group_cmd_tokens(t_token *head);
t_token *lexer(char *input);

t_node *create_node_parsing(t_node_type type, char *value);
t_redirection *create_redirection_parsing(char *filename, bool is_double);
void append_redirection(t_redirection **head, t_redirection *new_redir);
t_node *create_node_from_tokens(t_token *tokens);
t_node *convert_tokens_to_nodes(t_token *tokens);
t_node *parser(t_token *tokens);

bool ft_is_builtin(char *command);
void mark_builtins(t_node *head);
void ft_is_last_cmd(t_node *head);
char *expand_env_variables(const char *input);
void expand_node_values(t_node *head);
void free_nodes(t_node *head);
void ft_expenser(t_node *head);

// exec
static int execute_builtin(t_node *cmd, char **env);
static int execute_command(t_node *cmd, char **env);
static int execute_simple_command(t_node *cmd, char **env);
int exec(t_node *cmd, char **env);
t_node	*create_node(int type, char *value, bool builtin);
t_redirections *create_redirection(char *filename, int type);
t_node *create_test_node(char *value, bool is_last);
void free_redirections(t_redirection *redir);
void free_command_list(t_node *cmd);
void test_execution(char **env);
int execute_main(char **env);

// builtins
void        ft_exit(char *line);

int         ft_cd(char *path);

int        ft_echo(char *args);
static bool check_n_flag(const char *str, int *i);
static void	print_char(char c, char next_c);
static void	pre_print(const char *str, int *i);

void        ft_env(char **envp);

void        ft_pwd(void);

void        ft_export(char *args, char **env);

void        ft_unset(char *args, char **env);

#endif
