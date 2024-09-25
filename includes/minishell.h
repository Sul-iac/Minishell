#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>

typedef enum e_token_type {
	CMD,        // Command and its arguments
	PIPE,       // Pipe '|'
	REDIR_IN,   // Redirection input '<'
	REDIR_HEREDOC, // Heredoc '<<'
	REDIR_OUT,  // Redirection output '>'
	REDIR_APPEND // Append output '>>'
} t_token_type;

typedef struct s_token {
	char *value;
	t_token_type type;
	struct s_token *next;
} t_token;

//=========================
// main.c
void	ft_parsing(char *line);
void    ft_getline(char **line, size_t *len);

// lexer.c
t_token	*new_token(char *value, t_token_type type);
void	add_token(t_token **token_list, char *value, t_token_type type);
void    lexer(char *input);

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
