/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:23:34 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/07 17:34:57 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*tokenize_string(char *input)
{
	t_token	*head;
	char	*ptr;

	head = NULL;
	ptr = input;
	while (*ptr)
	{
		skip_spaces(&ptr);
		if (*ptr == '|' || *ptr == '<' || *ptr == '>')
			process_operator_token(&ptr, &head);
		else if (*ptr != '\0')
			process_command_token(&ptr, &head);
	}
	return (head);
}

t_token	*process_operator_token(char **ptr, t_token **head)
{
	char	operator[3] = {0};
	size_t	len;

	len = 1;
	if ((*ptr)[0] == '>' && (*ptr)[1] == '>')
		len = 2;
	else if ((*ptr)[0] == '<' && (*ptr)[1] == '<')
		len = 2;
	strncpy(operator, *ptr, len);
	operator[len] = '\0';
	*ptr += len;
	skip_spaces(ptr);
	return (process_redirection_target(ptr, head, operator));
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
