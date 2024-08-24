/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:19:38 by qbarron           #+#    #+#             */
/*   Updated: 2024/08/24 19:04:19 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// infos: j'ai du mettre les fonctions standard parceque flemme de link le makefile de la libft et tout


// creer les tokens
t_token	*create_tokens(t_token_type *type, const char *value)
{
	t_token *token;

	token = malloc(sizeof(t_token));
	if(token == NULL)
		return(NULL);											// envoyer a la fonction d'erreur pour free.
	token->type = type;											// met le type de token correspondant dans la strcture
	token->value = strdup(value);								// duplique 
	return(token);
}

// verifie si l'input est une commande ou une option
const char	*tokenize_commands_options(const char *start, const char *end,
							t_token **tokens, int *count_token)
{
	int				length;
	char			*value;
	t_token_type	*type;
	
	if(isalpha(*start) || *start == '-')								// si la fonction retourne 0, ou qu'on rencontre un tiret
		{
			end = start;												// on initalise afin de trouver les options
			while(isalnum(*end) || *end == '-' || *end == '/')
				end++;
			length = end - start;
			value = strndup(start, length);								// malloc la commande ou l'option
			type = NULL;												
			if(*start == '-')											// s'il y a un tiret, c'est une option
				type = &token_types[1];
			else														// sinon c'est une commande
				type = &token_types[0];
			tokens[(*count_token)++] = create_tokens(type, value);		// on creer le token
			start = end;												// on reinitialise pour continuer
			free(value);
		}
		return(start);
}


// verifie si operateur complexe
const char	*tokenize_complex_operators(const char *start, t_token **tokens, int *count_token)
{
		if(start[0] == '>' && start[1] == '>')									// si les deux premiers characteres sont complex
		{
			tokens[(*count_token)++] = create_tokens(&token_types[7], ">>");	// on creer
			start += 2;
		}
		else if(start[0] == '<' && start[1] == '<')								// pareil
		{
			tokens[(*count_token)++] = create_tokens(&token_types[8], "<<");
			start += 2;
		}
		return(start);
}

// verifie si l'input est un operateur
const char	*tokenize_operators(const char *start, t_token **tokens, int *count_token)
{
		if(*start == '|')													// fais la meme chose que tokenize_complex_operator
		{
			tokens[(*count_token)++] = create_tokens(&token_types[4], "|");			
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
		while(isspace(*start))															// on skippe les whitespaces s'il y en a
			start++;
		if(*start == '\0')																// verifie si il y a qqchs
			break ; 
		start = tokenize_commands_options(start, end, tokens, &count_token);			// tokenise les commandes et options
		start = tokenize_operators(start, tokens, &count_token);						// tokenise les operateurs communs
		if((start[0] == '>' && start[1] == '>') || (start[0] == '<' && start[1] == '<'))
			start = tokenize_complex_operators(start, tokens, &count_token);			// tokenise les operateurs complexes
		start++;
	}
	for (int i = 0; i < count_token; i++) {
        printf("Token type: %s, value: %s\n", tokens[i]->type->name, tokens[i]->value);	// print (pour le test)
        free(tokens[i]->value);
        free(tokens[i]);
    }
    return 0;
}
