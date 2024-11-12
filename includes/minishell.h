/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:19:19 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/12 16:49:10 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../src/libft/includes/libft.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define BOLD "\001\033[1m\002"
# define RESET "\001\033[0m\002"
# define CYAN "\001\033[36m\002"
# define BLUE "\001\033[34m\002"
# define GREEN "\001\033[32m\002"
# define YELLOW "\001\033[33m\002"
# define RED "\001\033[31m\002"

extern int				g_global_sig;

typedef enum e_token_type
{
	CMD,
	PIPE,
	REDIR_IN,
	REDIR_HEREDOC,
	REDIR_OUT,
	REDIR_APPEND
}						t_token_type;

typedef struct s_token
{
	char				*value;
	t_token_type		type;
	struct s_token		*next;
}						t_token;

typedef enum e_node_type
{
	CMD_2,
	PIPE_2,
	EMPTY_CMD
}						t_node_type;

typedef struct redirection
{
	char				*filename;
	bool				is_double;
	struct redirection	*next;
}						t_redirection;

typedef struct s_node
{
	t_node_type			type;
	char				*value;
	struct s_node		*next;
	t_redirection		*inputs;
	t_redirection		*outputs;
	bool				builtin;
	bool				is_last_cmd;
}						t_node;

typedef struct s_token_list
{
	t_token				*head;
	t_token				*tail;
}						t_token_list;

typedef struct s_data
{
	size_t				i;
	size_t				j;
	size_t				k;
}						t_process_data;

typedef struct s_main
{
	int					is_running;
}						t_main;

typedef struct s_pipe_data
{
	int		in_fd;
	int		cmd_index;
	pid_t	*pids;
	char	***env;
}				t_pipe_data;

typedef struct s_split_info
{
	char	**str_array;
	size_t	start;
	int		index;
	int		num_pipes;
}				t_split_info;

// expenser les variable d'environnement

//=========================

// expenser.c
bool					ft_is_builtin(char *command);
void					mark_builtins(t_node *head);
void					ft_is_last_cmd(t_node *head);
void					ft_expenser(t_node *head);

// expenser_2.c
char					*get_env_variable_value(const char *input, size_t *i);
char					*expand_env_variables(const char *input);
void					expand_node_values(t_node *head);
char					*resize_result_if_needed(char *result,
							size_t *result_size, size_t required_size);

// expenser_3.c
int						handle_quotes(const char *p, t_process_data *data,
							int *in_single_quote, int *in_double_quote);
char					*handle_variable_replacement(const char *p,
							t_process_data *data, char *result);
char					*process_input(const char *p,
							t_process_data *data, char *result);

// free_parsing.c
void					free_nodes(t_node *head);
void					free_split_array(char **array);
void					free_tokens(t_token *head);
void					free_redirections(t_redirection *redir);
void					free_array(char **str_array, int count);

// lexer_group_cmd.c
char					*group_consecutive_cmd_tokens(t_token **temp,
							size_t *grouped_len);
t_token					*group_cmd_tokens(t_token *head);

// lexer_lexer_concat_create.c
void					skip_spaces(char **input);
t_token					*create_token(char *value, t_token_type type);
void					append_token(t_token **head, t_token *new_token);
t_token					*concat_tokens(t_token *head1, t_token *head2);
t_token					*lexer(char *input);

// lexer_reorganize.c
t_token					*add_token_to_list(t_token **head,
							t_token **tail, t_token *token);
void					separate_tokens(t_token *current,
							t_token_list *cmd_list, t_token_list *other_list);
t_token					*reorganize_tokens(t_token *head);

//lexer_split_string.c
int						count_pipes(const char *input);
char					*allocate_and_copy(const char *start, size_t length);
int						process_segment(const char *input, t_split_info *info);
char					**split_into_array(const char *input, int num_pipes);
char					**split_string(const char *input);

// lexer_tokenize.c
t_token					*process_operator_token(char **ptr, t_token **head);
t_token					*process_command_token(char **ptr, t_token **head);
t_token_type			determine_type(char *token);
t_token					*process_redirection_target(char **ptr,
							t_token **head, char operator[3]);
t_token					*tokenize_string(char *input);

// parser_2.c
t_node					*create_node_from_tokens(t_token *tokens);
char					*build_command_value(t_token *tokens);
void					gather_redirections(t_token *tokens,
							t_redirection **inputs, t_redirection **outputs);

// parser_3.c
t_node					*convert_tokens_to_nodes(t_token *tokens);
t_node					*process_command_tokens(t_node **node_head,
							t_node *node_tail, t_token *cmd_tokens);
t_node					*append_pipe_node(t_node *node_tail);

// parser.c
t_node					*create_node(t_node_type type, char *value);
t_redirection			*create_redirection(char *filename, bool is_double);
void					append_redirection(t_redirection **head,
							t_redirection *new_redir);
t_node					*parser(t_token *tokens);

// solo builtins
void					ft_pwd(void);
int						ft_cd(char *path);
int						ft_exit(char **arg);
void					ft_echo(char **args);
void					ft_env(char ***envp);
char					**ft_unset(char *arg, char ***env);

// export
void					sort_env(char ***env);
char					*get_var_name(const char *var);
void					display_sorted_env(char **env);
int						is_valid_identifier(const char *var);
char					**ft_export(char *args, char ***env);
int						var_exists(char ***env, char *var_name);
void					export_utils(char **new_vars, char ***env, int env_size,
							int *i);

// exec
void					exec(t_node *cmd, char ***env);
int						execute_builtin(t_node *cmd, char ***env);
int						execute_command(t_node *cmd, char ***env);
int						execute_simple_command(t_node *cmd, char ***env);

// pipes
void					handle_fork_error(pid_t *pids);
void					parent_process(int *in_fd, int *fd);
int						execute_pipes(t_node *cmd, char ***env);
void					handle_pipe_creation(t_node *cmd, int fd[2]);
void					child_process(t_node *cmd, char ***env, int in_fd,
							int *fd);
void					process_command(t_node *cmd, t_pipe_data *data);
void					wait_all_processes(t_pipe_data *data, int cmd_count);
void					close_all_child_process(int *fd, t_node *cmd,
							char ***env);
void					execute_builtin_nbuiltin(t_node *cmd, char ***env);

t_pipe_data				*init_pipe_data(char ***env);
pid_t					*init_pipe_execution(t_node *cmd, int *cmd_count);

char					*get_path(char *cmd, char ***env);

// redirs, heredoc
int						handle_heredoc(char *delimiter);
int						handle_input_redirection(const char *file);
int						process_input_redirections(t_redirection *current);
int						handle_heredoc_redirection(char *filename, int *fd);
int						process_output_redirections(t_redirection *current);
int						handle_output_redirection(const char *file, int flags);
int						handle_redirections(t_node *cmd);
void					handle_sigint_heredoc(int signum);
void					handle_heredoc_input(int pipefd[2], char *delimiter);

// signaux
void					reset_signal(void);
void					signal_handler(int signo);

// fork
char					*get_first_word(const char *str);
void					forked_commands(char *cmd, char ***env);
char					**nforked_commands(char *cmd, char ***env);

// errors/free exec
void					free_and_error(char *ptr, char **ptr2, char *msg,
							bool error);
void					free_triple_pointer(char ***array);
void					ft_free_array(char **array);
void					cleanup_cmd(t_node *cmd);

// main
char					*ft_readline(void);
char					*ft_create_prompt(void);
char					**copy_env(char **original_env);
void					init_shell(char ***envp, t_main *main);
void					init_parser_exec(char *line, t_main *main,
							char ***envp);
void					execute_relative_absolute(char *cmd, char **args,
							char ***envp);
void					exit_program(t_node *head, char *line, t_main *main,
							char ***envp);

// cleaning
void					clean_node(t_node *node);
void					clean_nodes(t_node *head);
void					clean_token(t_token *token);
void					clean_tokens(t_token *tokens);

#endif
