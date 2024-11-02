#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <ctype.h>
# include <stddef.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/history.h>
# include <readline/readline.h>
# include "../src/libft/libft.h"

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
char	*get_env_variable_value(const char *input, size_t *i);

// expenser_2.c
char	*process_input(const char *input, size_t *i, size_t *j, char *result, size_t *result_size);
char	*expand_env_variables(const char *input);
void	expand_node_values(t_node *head);
void	ft_expenser(t_node *head);
char	*resize_result_if_needed(char *result, size_t *result_size, size_t required_size);

// free_nodes.c
void	free_nodes(t_node *head);
void	free_split_array(char **array);
void	free_tokens(t_token *head);
void	free_redirections(t_redirection *redir);

//lexer_2.c
t_token	*create_token(char *value, t_token_type type);
void	append_token(t_token **head, t_token *new_token);
t_token_type	determine_type(char *token);
void	skip_spaces(char **input);
char	*extract_quoted_string(char **input);

//lexer_3.c
t_token	*tokenize_string(char *input);
t_token	*process_quoted_token(char **ptr, t_token **head);
t_token	*process_operator_token(char **ptr, t_token **head);
t_token	*process_redirection_target(char **ptr, t_token **head, char operator[3]);

//lexer_4.c
t_token	*process_command_token(char **ptr, t_token **head);
t_token	*add_token_to_list(t_token **head, t_token **tail, t_token *token);
void	separate_tokens(t_token *current, t_token **cmd_head, t_token **cmd_tail, t_token **other_head, t_token **other_tail);
t_token	*reorganize_tokens(t_token *head);

//lexer_5.c
int	count_pipes(const char *input);
char	*allocate_and_copy(const char *start, size_t length);
char	**split_into_array(const char *input, int num_pipes);
char	**split_string(const char *input);
t_token	*concat_tokens(t_token *head1, t_token *head2);

//lexer.c
char	*group_consecutive_cmd_tokens(t_token **temp, size_t *grouped_len);
t_token	*group_cmd_tokens(t_token *head);
t_token	*lexer(char *input);

//parser_2.c
t_node	*create_node_from_tokens(t_token *tokens);
char	*build_command_value(t_token *tokens);
void	gather_redirections(t_token *tokens, t_redirection **inputs, t_redirection **outputs);

//parser_3.c
t_node	*convert_tokens_to_nodes(t_token *tokens);
t_node	*process_command_tokens(t_node **node_head, t_node *node_tail, t_token *cmd_tokens);
t_node	*append_pipe_node(t_node *node_tail);

//parser.c
t_node	*create_node(t_node_type type, char *value);
t_redirection	*create_redirection(char *filename, bool is_double);
void	append_redirection(t_redirection **head, t_redirection *new_redir);
t_node	*parser(t_token *tokens);

// //testeur_parsing.c
// void print_token(t_token *token);
// void print_redirection(t_redirection *redir);
// void print_node(t_node *node);

int	ft_cd(char *path);

bool check_n_flag(const char *str, int *i);
void	print_char(char c, char next_c);
void	pre_print(const char *str, int *i);
int ft_echo(char *str);

void    ft_env(char ***envp);

void    ft_exit(char *line);

int is_valid_identifier(const char *var);
char *get_var_name(const char *var);
int var_exists(char ***env, char *var_name);
void sort_env(char ***env);
void display_sorted_env(char **env);
char **ft_export(char *args, char ***env);

void    ft_pwd(void);

char *get_var_name(const char *var);
char **ft_unset(char *arg, char ***env);

// exec
int execute_builtin(t_node *cmd, char ***env);
int execute_command(t_node *cmd, char ***env);
int execute_simple_command(t_node *cmd, char ***env);
int exec(t_node *cmd, char ***env);

void	child_process(t_node *cmd, char ***env, int in_fd, int *fd);
void	parent_process(int *in_fd, int *fd, pid_t pid);
void	execute_pipes(t_node *cmd, char ***env);
char *get_path(char *cmd, char ***env);

void handle_redirections(t_node *cmd);

char	*get_first_word(const char *str);
bool	is_builtin(const char *cmd);
void	forked_commands(char *cmd, char ***env);
char	**nforked_commands(char *cmd, char ***env);
void	free_and_error(char *ptr, char **ptr2, char *msg, bool error);

void    ft_free_array(char **array);

//main
void ft_readline(char **line);
char **copy_env(char **original_env);
void init_shell(char *line, char ***envp);


#endif
