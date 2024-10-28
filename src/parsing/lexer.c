/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:08:52 by tgerardi          #+#    #+#             */
/*   Updated: 2024/09/24 23:08:52 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = strdup(value);
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_token **head, t_token *new_token)
{
	t_token	*temp;

	if (*head == NULL)
	{
		*head = new_token;
	}
	else
	{
		temp = *head;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = new_token;
	}
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

void	skip_spaces(char **input)
{
	while (**input == ' ' || **input == '\t')
	{
		(*input)++;
	}
}

char	*extract_quoted_string(char **input)
{
	char	*start;
	char	quote_type;
	char	*end;
	size_t	len;
	char	*quoted_string;

	start = *input;
	quote_type = *start;
	end = start + 1;
	while (*end && *end != quote_type)
	{
		if (*end == '\\' && *(end + 1) == quote_type)
		{
			end++;
		}
		end++;
	}
	if (*end == quote_type)
	{
		len = end - start + 1;
		quoted_string = (char *)malloc(len + 1);
		strncpy(quoted_string, start, len);
		quoted_string[len] = '\0';
		*input = end + 1;
		return (quoted_string);
	}
	return (NULL);
}

t_token	*tokenize_string(char *input)
{
	t_token	*head;
	char	*ptr;
	char	*quoted_token;
	char	operator[3] = {0};
	size_t	len;
	char	*redirection_target;
	char	*start;
	char	*cmd_token;

	head = NULL;
	ptr = input;
	while (*ptr)
	{
		skip_spaces(&ptr);
		if (*ptr == '\'' || *ptr == '"')
		{
			quoted_token = extract_quoted_string(&ptr);
			if (quoted_token)
			{
				append_token(&head, create_token(quoted_token, CMD));
				free(quoted_token);
			}
		}
		else if (*ptr == '|' || *ptr == '<' || *ptr == '>')
		{
			len = 1;
			if ((*ptr == '>' && *(ptr + 1) == '>') || (*ptr == '<' && *(ptr
						+ 1) == '<'))
			{
				len = 2;
			}
			strncpy(operator, ptr, len);
			operator[len] = '\0';
			ptr += len;
			skip_spaces(&ptr);
			if (*ptr && *ptr != '|' && *ptr != '<' && *ptr != '>')
			{
				start = ptr;
				while (*ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '|'
					&& *ptr != '<' && *ptr != '>')
				{
					ptr++;
				}
				len = ptr - start;
				redirection_target = (char *)malloc(len + 1);
				strncpy(redirection_target, start, len);
				redirection_target[len] = '\0';
				append_token(&head, create_token(redirection_target,
						determine_type(operator)));
				free(redirection_target);
			}
		}
		else if (*ptr != '\0')
		{
			start = ptr;
			while (*ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '|'
				&& *ptr != '<' && *ptr != '>')
			{
				ptr++;
			}
			len = ptr - start;
			cmd_token = (char *)malloc(len + 1);
			strncpy(cmd_token, start, len);
			cmd_token[len] = '\0';
			append_token(&head, create_token(cmd_token, CMD));
			free(cmd_token);
		}
	}
	return (head);
}

t_token	*reorganize_tokens(t_token *head)
{
	t_token	*cmd_head;
	t_token	*cmd_tail;
	t_token	*other_head;
	t_token	*other_tail;
	t_token	*current;
	t_token	*next;

	cmd_head = NULL;
	cmd_tail = NULL;
	other_head = NULL;
	other_tail = NULL;
	current = head;
	while (current)
	{
		next = current->next;
		current->next = NULL;
		if (current->type == CMD)
		{
			if (!cmd_head)
			{
				cmd_head = current;
				cmd_tail = current;
			}
			else
			{
				cmd_tail->next = current;
				cmd_tail = cmd_tail->next;
			}
		}
		else
		{
			if (!other_head)
			{
				other_head = current;
				other_tail = current;
			}
			else
			{
				other_tail->next = current;
				other_tail = other_tail->next;
			}
		}
		current = next;
	}
	if (cmd_tail)
	{
		cmd_tail->next = other_head;
	}
	return (cmd_head ? cmd_head : other_head);
}

char	**split_string(const char *input)
{
	int			num_pipes;
	const char	*ptr = input;
	char		**str_array;
	size_t		start;
	int			index;
	const char	*pipe_pos = strchr(input + start, '|');
	size_t		length;

	num_pipes = 0;
	while ((ptr = strchr(ptr, '|')) != NULL)
	{
		num_pipes++;
		ptr++;
	}
	str_array = malloc((num_pipes + 2) * sizeof(char *));
	if (str_array == NULL)
	{
		return (NULL);
	}
	start = 0;
	index = 0;
	while (index <= num_pipes)
	{
		length = (pipe_pos != NULL) ? (size_t)(pipe_pos - (input
					+ start)) : strlen(input + start);
		str_array[index] = malloc((length + 1) * sizeof(char));
		if (str_array[index] == NULL)
		{
			for (int j = 0; j < index; j++)
			{
				free(str_array[j]);
			}
			free(str_array);
			return (NULL);
		}
		strncpy(str_array[index], input + start, length);
		str_array[index][length] = '\0';
		start += length + 1;
		index++;
	}
	str_array[index] = NULL;
	return (str_array);
}

void	free_tokens(t_token *head)
{
	t_token	*temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp->value);
		free(temp);
	}
}

void	free_split_array(char **array)
{
	for (int i = 0; array[i]; i++)
	{
		free(array[i]);
	}
	free(array);
}

t_token	*concat_tokens(t_token *head1, t_token *head2)
{
	t_token	*current;
	t_token	*pipe_token;

	if (!head1)
		return (head2);
	if (!head2)
		return (head1);
	current = head1;
	while (current->next)
	{
		current = current->next;
	}
	pipe_token = create_token("|", PIPE);
	current->next = pipe_token;
	current->next->next = head2;
	return (head1);
}

t_token	*group_cmd_tokens(t_token *head)
{
	t_token	*grouped_head;
	t_token	*temp;
	char	*grouped_value;
	size_t	grouped_len;
	t_token	*new_cmd_token;

	grouped_head = NULL;
	temp = head;
	while (temp)
	{
		if (temp->type == CMD)
		{
			grouped_value = strdup(temp->value);
			grouped_len = strlen(grouped_value);
			while (temp->next && temp->next->type == CMD)
			{
				temp = temp->next;
				grouped_len += strlen(temp->value) + 1;
				grouped_value = (char *)realloc(grouped_value, grouped_len + 1);
				strcat(grouped_value, " ");
				strcat(grouped_value, temp->value);
			}
			new_cmd_token = create_token(grouped_value, CMD);
			append_token(&grouped_head, new_cmd_token);
			free(grouped_value);
		}
		else
		{
			append_token(&grouped_head, create_token(temp->value, temp->type));
		}
		temp = temp->next;
	}
	return (grouped_head);
}

t_token	*lexer(char *input)
{
	char **str = split_string(input);

	t_token *final_tokens = NULL;

	for (int j = 0; str[j]; j++)
	{
		t_token *tokens = tokenize_string(str[j]);
		if (tokens)
		{
			tokens = reorganize_tokens(tokens);
			tokens = group_cmd_tokens(tokens);
			final_tokens = concat_tokens(final_tokens, tokens);
		}
	}
	free_split_array(str);
	return (final_tokens);
}