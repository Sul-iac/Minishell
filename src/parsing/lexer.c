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
    t_token *token;

    token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->value = strdup(value);
    token->type = type;
    token->next = NULL;
    return token;
}

void add_token(t_token **token_list, char *value, t_token_type type)
{
    t_token *new;

    new = new_token(value, type);
    if (!new)
        return;
    new->next = *token_list;
    *token_list = new;
}

void handle_quotes(char **input, t_token **token_list)
{
    char *start;
    char quote;
    char *quoted_str;

    start = *input;
    quote = **input;
    (*input)++;
    while (**input && **input != quote)
        (*input)++;
    quoted_str = strndup(start + 1, *input - start - 1);
    add_token(token_list, quoted_str, CMD);
    free(quoted_str);
    (*input)++;
}

char *replace_env_vars(char *token_str)
{
    char *result;
    char *dollar;
    char *var_value;
    char *end;
    char *var_name;
    size_t before_dollar_len;
    char *new_result;

    result = strdup(token_str);
    dollar = strchr(result, '$');
    while (dollar)
    {
        var_name = dollar + 1;
        end = var_name;
        while (*end && (isalnum(*end) || *end == '_'))
            end++;
        var_value = getenv(strndup(var_name, end - var_name));
        if (var_value)
        {
            before_dollar_len = dollar - result;
            new_result = malloc(before_dollar_len + strlen(var_value) + strlen(end) + 1);
            strncpy(new_result, result, before_dollar_len);
            strcpy(new_result + before_dollar_len, var_value);
            strcat(new_result, end);
            free(result);
            result = new_result;
        }
        dollar = strchr(result, '$');
    }
    return result;
}

void handle_redirection(char **input, t_token **token_list)
{
    char *token_str;

    token_str = *input;
    if (strcmp(token_str, "<") == 0)
    {
        add_token(token_list, token_str, REDIR_IN);
    } 
    else if (strcmp(token_str, ">") == 0)
    {
        add_token(token_list, token_str, REDIR_OUT);
    } 
    else if (strcmp(token_str, ">>") == 0)
    {
        add_token(token_list, token_str, REDIR_APPEND);
    }
    (*input)++;
    token_str = strtok(NULL, " ");
    if (token_str)
    {
        add_token(token_list, token_str, CMD);
    }
}

void lexer(char *input, t_token **token_list)
{
    char *token_str;
    char *expanded_str;

    while (*input)
    {
        if (*input == ' ')
        {
            input++;
            continue;
        }
        else if (*input == '\'' || *input == '"')
        {
            handle_quotes(&input, token_list);
        }
        else if (*input == '<' || *input == '>')
        {
            handle_redirection(&input, token_list);
        }
        else
        {
            char *start = input;
            while (*input && *input != ' ' && *input != '<' && *input != '>' && *input != '\'' && *input != '"')
                input++;
            token_str = strndup(start, input - start);
            expanded_str = replace_env_vars(token_str);
            add_token(token_list, expanded_str, CMD);
            free(token_str);
            free(expanded_str);
        }
    }
}
