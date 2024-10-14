#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>
# include <ctype.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../src/libft/libft.h"

# define MAX_ARGS 10

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

typedef struct s_node {				//from parser/exp. to exec
	t_token_type	type;
    char            *value;
    t_redirection   *inputs; // < et <<
    t_redirection   *outputs; // > et >>
    bool            builtin;
    bool            is_last_cmd;
    struct s_node   *next;
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





//======================//
// builtins				//
//======================//

// cd.c
void    ft_cd(char *args);

// echo.c
void    ft_echo(char *args);

// env.c
void    ft_env(char *args);

// pwd.c
void    ft_pwd(void);

// export.c
void    ft_export(char *args);

// unset.c
void    ft_unset(char *args);


//======================//
// Utils				//
//======================//

// error.c
void	error(void);

//======================//
// Exec					//
//======================//

int	execute_pipe(t_node *cmd);
int	execute_main(char **env);
int	exec(t_node *cmd, char **env);

void	exec_test(char **env);
void	parse_nbuiltin(t_node *cmd, char **env);

char	*get_path(char *cmd, char **env);

#endif
