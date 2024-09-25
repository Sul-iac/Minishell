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

#include "minishell.h"

t_token *new_token(char *value, t_token_type type)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = strdup(value);
    token->type = type;
    token->next = NULL;
    return token;
}

void add_token(t_token **token_list, char *value, t_token_type type)
{
    t_token *new = new_token(value, type);
    if (!new)
        return;
    new->next = *token_list;
    *token_list = new;
}

void lexer(char *input)
{
    char *token_str = strtok(input, " ");
    while (token_str) {
        if (strcmp(token_str, "|") == 0)
            add_token(&token_list, token_str, PIPE);
        else if (strcmp(token_str, ">") == 0)
            add_token(&token_list, token_str, REDIR_OUT);
        else if (strcmp(token_str, ">>") == 0)
            add_token(&token_list, token_str, REDIR_APPEND);
        else
            add_token(&token_list, token_str, CMD);
        token_str = strtok(NULL, " ");
    }
}