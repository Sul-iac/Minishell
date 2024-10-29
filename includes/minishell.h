#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <ctype.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
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
    REDIR_APPEND,
	EMPTY_CMD
} t_token_type;

typedef struct s_token {
    char            *value;
    t_token_type    type;
    struct s_token  *next;
} t_token;

typedef struct redirection {
    char                *filename;
    bool                is_double; //0 < > 1 << >>
    struct redirection  *next;
} t_redirection;

typedef enum e_node_type {
    CMD_2,
    PIPE_2,
    // EMPTY_CMD // a voir pour si y'a juste une redir donc pas de value de node
} t_node_type;

typedef struct s_node {				//from parser/exp. to exec
	t_token_type	type;
    char            *value;
    t_redirection   *inputs; // < et <<
    t_redirection   *outputs; // > et >>
    bool            builtin;
    bool            is_last_cmd;
    struct s_node   *next;
} t_node;

//======================//
// main.c				//
//======================//

void						ft_parsing(char *line);
void						ft_getline(char **line, size_t *len);

// lexer.c
t_token						*new_token(char *value, t_token_type type);
void						add_token(t_token **token_list, char *value, t_token_type type);
void						lexer(char *input, t_token **token_list);


//======================//
// 		builtins		//
//======================//

// cd.c			
int							ft_cd(char *path);

// echo.c			
int 						ft_echo(char *args);

// export.c
char						**ft_export(char *args, char **env);

// unset.c
char						**ft_unset(char *args, char **env);



void						ft_pwd(void);
void    					ft_env(char **envp);
void						ft_exit(char *line);


//======================//
// 		Utils			//
//======================//

// error.c
void						error(void);
void						ft_free_array(char **array);
//======================//
// 		Exec			//
//======================//

int							exec(t_node *cmd, char **env);
int							execute_pipes(t_node *cmd, char **env);
int							execute_simple_command(t_node *cmd, char **env);

char						*get_path(char *cmd, char **env);
char						*get_first_word(const char *str);
char						**nforked_commands(char *cmd, char **env);

void						handle_redirection(t_redirection *redirections, bool is_input);

void						forked_commands(char *cmd, char **env);

bool						is_builtin(const char *cmd);

//test exec ================================================================

typedef struct s_redirections
{
    char *filename;
    int type;
    struct s_redirection *next;
} t_redirections;

int							execute_main(char **env);
void						test_execution(char **env);
void						free_command_list(t_node *cmd);
void						free_redirections(t_redirection *redir);
t_node						*create_test_node(char *value, bool is_last);
t_node						*create_node(int type, char *value, bool builtin);
t_redirection				*create_redirection(char *filename, bool is_double);







#endif
