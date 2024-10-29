/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 14:23:34 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/29 14:23:34 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *tokenize_string(char *input)
{
    t_token *head = NULL;
    char *ptr = input;

    while (*ptr)
    {
        skip_spaces(&ptr);

        if (*ptr == '\'' || *ptr == '"')
        {
            process_quoted_token(&ptr, &head);
        }
        else if (*ptr == '|' || *ptr == '<' || *ptr == '>')
        {
            process_operator_token(&ptr, &head);
        }
        else if (*ptr != '\0')
        {
            process_command_token(&ptr, &head);
        }
    }
    return head;
}

t_token *process_quoted_token(char **ptr, t_token **head)
{
    char *quoted_token = extract_quoted_string(ptr);
    if (quoted_token)
    {
        append_token(head, create_token(quoted_token, CMD));
        free(quoted_token);
    }
    return *head;
}

t_token *process_operator_token(char **ptr, t_token **head)
{
    char operator[3] = {0};
    size_t len = 1;

    if ((*ptr == '>' && *(ptr + 1) == '>') || (*ptr == '<' && *(ptr + 1) == '<'))
    {
        len = 2;
    }
    
    strncpy(operator, *ptr, len);
    operator[len] = '\0';
    *ptr += len;
    skip_spaces(ptr);

    if (**ptr && **ptr != '|' && **ptr != '<' && **ptr != '>')
    {
        char *start = *ptr;
        while (**ptr && **ptr != ' ' && **ptr != '\t' && **ptr != '|' && **ptr != '<' && **ptr != '>')
        {
            (*ptr)++;
        }
        size_t length = *ptr - start;
        char *redirection_target = (char *)malloc(length + 1);
        strncpy(redirection_target, start, length);
        redirection_target[length] = '\0';
        append_token(head, create_token(redirection_target, determine_type(operator)));
        free(redirection_target);
    }
    return *head;
}