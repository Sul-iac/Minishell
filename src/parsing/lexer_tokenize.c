/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokenize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:34:10 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/12 14:34:10 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*process_operator_token(char **ptr, t_token **head)
{
	char	operator[3];
	size_t	len;

	len = 1;
	if ((*ptr)[0] == '>' && (*ptr)[1] == '>')
		len = 2;
	else if ((*ptr)[0] == '<' && (*ptr)[1] == '<')
		len = 2;
	memset(operator, 0, sizeof(operator));
	strncpy(operator, *ptr, len);
	operator[len] = '\0';
	*ptr += len;
	skip_spaces(ptr);
	return (process_redirection_target(ptr, head, operator));
}

t_token	*process_command_token(char **ptr, t_token **head)
{
	char	*debut;
	size_t	lenlen;
	char	*cmd_token;

	debut = *ptr;
	while (**ptr && **ptr != ' ' && **ptr != '\t')
	{
		(*ptr)++;
	}
	lenlen = *ptr - debut;
	cmd_token = (char *)malloc(lenlen + 1);
	strncpy(cmd_token, debut, lenlen);
	cmd_token[lenlen] = '\0';
	append_token(head, create_token(cmd_token, CMD));
	free(cmd_token);
	return (*head);
}

t_token_type	determine_type(char *token)
{
	if (strcmp(token, "|") == 0)
		return (PIPE);
	if (strncmp(token, ">>", 2) == 0)
		return (REDIR_APPEND);
	if (strncmp(token, ">", 1) == 0)
		return (REDIR_OUT);
	if (strncmp(token, "<<", 2) == 0)
		return (REDIR_HEREDOC);
	if (strncmp(token, "<", 1) == 0)
		return (REDIR_IN);
	return (CMD);
}

t_token	*process_redirection_target(char **ptr,
	t_token **head, char operator[3])
{
	char	*start;
	size_t	length;
	char	*redirection_target;

	if (**ptr && **ptr != '|' && **ptr != '<' && **ptr != '>')
	{
		start = *ptr;
		while (**ptr && **ptr != ' ' && **ptr != '\t' && **ptr != '|'
			&& **ptr != '<' && **ptr != '>')
			(*ptr)++;
		length = *ptr - start;
		redirection_target = (char *)malloc(length + 1);
		if (!redirection_target)
			return (NULL);
		strncpy(redirection_target, start, length);
		redirection_target[length] = '\0';
		append_token(head, create_token(redirection_target,
				determine_type(operator)));
		free(redirection_target);
	}
	return (*head);
}

t_token	*tokenize_string(char *input)
{
	t_token		*head;
	char		*ptr;
	static int	quote_count;

	quote_count = 0;
	head = NULL;
	ptr = input;
	while (*ptr)
	{
		skip_spaces(&ptr);
		if (*ptr == '\'' || *ptr == '"')
			quote_count++;
		if ((*ptr == '<' || *ptr == '>') && quote_count % 2 == 0)
			process_operator_token(&ptr, &head);
		else if (*ptr != '\0')
			process_command_token(&ptr, &head);
	}
	return (head);
}
