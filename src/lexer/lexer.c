/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:19:38 by qbarron           #+#    #+#             */
/*   Updated: 2024/08/24 18:25:43 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// creer les tokens
t_token	*create_tokens(t_token_type *type, const char *value)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if(token == NULL)
		return(NULL);			// envoyer a la fonction d'erreur pour free.
	token->type = type;
	token->value = strdup(value);
	return(token);
}

// verifie si l'input est une chaine de charactere
const char	*tokenize_commands_options(const char *start, const char *end,
							t_token **tokens, int *count_token)
{
	int				length;
	char			*value;
	t_token_type	*type;
	
	if(isalpha(*start) || *start == '-')
		{
			end = start;
			while(isalnum(*end) || *end == '-' || *end == '/')
				end++;
			length = end - start;
			value = strndup(start, length);
			type = NULL;
			if(*start == '-')
				type = &token_types[1];				// options
			else
				type = &token_types[0];				// commandes
			tokens[(*count_token)++] = create_tokens(type, value);
			start = end;
			free(value);
		}
		return(start);
}

const char	*tokenize_complex_operators(const char *start, t_token **tokens, int *count_token)
{
		if(start[0] == '>' && start[1] == '>')
		{
			tokens[(*count_token)++] = create_tokens(&token_types[7], ">>");
			start += 2;
		}
		else if(start[0] == '<' && start[1] == '<')
		{
			tokens[(*count_token)++] = create_tokens(&token_types[8], "<<");
			start += 2;
		}
		return(start);
}

// verifie si l'input est un operateur
const char	*tokenize_operators(const char *start, t_token **tokens, int *count_token)
{
		if(*start == '|')
		{
			tokens[(*count_token)++] =  create_tokens(&token_types[4], "|");
			start++;
		}
		else if(*start == '>')
		{
			tokens[(*count_token)++] = create_tokens(&token_types[5], ">");
			start++;
		}
		else if(*start == '<')
		{
			tokens[(*count_token)++] = create_tokens(&token_types[6], "<");
			start++;
		}
		return(start);
}

// main (avec l'aide de chat gpt) pour test. Ce sera la fonction principale du lexer
int main()
{
    int				count_token;
	t_token			*tokens[100];
	const char		*start;
	const char		*end;
	char			*input;

	count_token = 0;
	input = "echo -n \"Bonjour\" | grep -i 'hello' > output.txt";
	start = input;
	end = NULL;
	while(*start)
	{
		while(isspace(*start))														// on skippe le whitespaces
			start++;
		if(*start == '\0')															// verifie si il y a qqchs
			break ; 
		start = tokenize_commands_options(start, end, tokens, &count_token);		// tokenise les commandes et options
		start = tokenize_operators(start, tokens, &count_token);					// tokenise les operateurs communs
		if((start[0] == '>' && start[1] == '>') || (start[0] == '<' && start[1] == '<'))
			start = tokenize_complex_operators(start, tokens, count_token);			// tokenise les operateurs complexes
		start++;
	}
	for (int i = 0; i < count_token; i++) {
        printf("Token type: %s, value: %s\n", tokens[i]->type->name, tokens[i]->value);		// print (pour le test)
        free(tokens[i]->value);
        free(tokens[i]);
    }
    return 0;
}
