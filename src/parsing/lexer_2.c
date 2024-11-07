/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:18:43 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/29 14:18:43 by tgerardi         ###   ########.fr       */
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

char *extract_quoted_string(char **input) {
    char *start;
    char quote_type;
    char *end;
    size_t len;
    char *quoted_string;

    start = *input;
    quote_type = *start;
    end = start + 1;

    while (*end) {
        if (*end == '\\' && *(end + 1) == quote_type) {
            // Gérer les guillemets échappés (ex : \" ou \')
            end++;
        } else if (quote_type == '\'' && *end == '\'') {
            // Si c'est une quote simple, on arrête la lecture à la fermeture de la quote simple
            break;
        } else if (quote_type == '"' && *end == '"') {
            // Si c'est une quote double, on arrête à la fermeture de la quote double
            break;
        }
        end++;
    }

    if (*end == quote_type) {
        // La longueur de la chaîne exclut les guillemets
        len = end - start - 1;
        quoted_string = (char *)malloc(len + 1);

        // Copie du contenu sans les guillemets
        strncpy(quoted_string, start + 1, len);
        quoted_string[len] = '\0';

        *input = end + 1;
        return quoted_string;
    }

    return NULL;
}

