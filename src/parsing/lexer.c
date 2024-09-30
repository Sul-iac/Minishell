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
    t_token *new = new_token(value, type);
    if (!new)
        return;

    if (*token_list == NULL) {
        *token_list = new;
    } else {
        t_token *current = *token_list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new;
    }
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
        char *var_name_str = strndup(var_name, end - var_name);
        var_value = getenv(var_name_str);
        free(var_name_str);
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

    token_str = strndup(*input, 1);
    if (strcmp(token_str, "<") == 0)
    {
        add_token(token_list, token_str, REDIR_IN);
    } 
    else if (strcmp(token_str, ">") == 0)
    {
        add_token(token_list, token_str, REDIR_OUT);
    }
    else if (strncmp(*input, ">>", 2) == 0)
    {
        free(token_str);
        token_str = strndup(*input, 2);
        add_token(token_list, token_str, REDIR_APPEND);
        (*input)++;
    }
    (*input)++;
    free(token_str);
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
const char *token_type_to_str(t_token_type type) {
    switch (type) {
        case CMD: return "CMD";
        case REDIR_IN: return "REDIR_IN";
        case REDIR_OUT: return "REDIR_OUT";
        case REDIR_APPEND: return "REDIR_APPEND";
        default: return "UNKNOWN";
    }
}

void print_token_list(t_token *token_list) {
    t_token *current = token_list;
    while (current != NULL) {
        printf("Token: %s, Type: %s\n", current->value, token_type_to_str(current->type));
        current = current->next;  // Passer au token suivant
    }
}

void free_token_list(t_token *token_list)
{
    t_token *current;
    while (token_list != NULL)
    {
        current = token_list;
        token_list = token_list->next;
        free(current->value);  // Libérer la valeur du token
        free(current);  // Libérer le token lui-même
    }
}

int main() {
    char *command = "echo \"Hello, $USER\" > output.txt";
    t_token *token_list = NULL;  // Liste de tokens, initialement vide

    // Affichage de la commande à tester
    printf("Commande testée: %s\n", command);

    // Appel du lexer pour analyser la commande
    lexer(command, &token_list);

    // Affichage de la liste des tokens générés par le lexer
    printf("\nTokens générés par le lexer:\n");
    print_token_list(token_list);

    // Libération de la liste de tokens
    free_token_list(token_list);

    return 0;
}
