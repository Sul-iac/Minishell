/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeur_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 15:51:03 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/28 15:51:03 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void print_token(t_token *token)
{
    while (token) {
        printf("Token Value: '%s', Type: %d\n", token->value, token->type);
        token = token->next;
    }
}

void print_redirection(t_redirection *redir)
{
    while (redir) {
        printf("\tRedirection Filename: '%s', Is Double: %d\n", redir->filename, redir->is_double);
        redir = redir->next;
    }
}

void print_node(t_node *node)
{
    while (node) {
        printf("Node Type: %d, Value: '%s'\n", node->type, node->value ? node->value : "NULL");
        printf("Inputs:\n");
        print_redirection(node->inputs);
        printf("Outputs:\n");
        print_redirection(node->outputs);
        printf("Builtin: %d, Is Last Cmd: %d\n\n", node->builtin, node->is_last_cmd);
        node = node->next;
    }
}

int main()
{
    char *input = " echo Makefile | $USER > output.tkt grep pr | >> output.txt head -n 5 | hello (NA) # check status code";

    t_token *tokens = lexer(input);
    if (!tokens) {
        fprintf(stderr, "Erreur de lexing.\n");
        return 1;
    }
    
    printf("Tokens:\n");
    print_token(tokens);

    t_node *head = parser(tokens);
    if (!head) {
        fprintf(stderr, "Erreur de parsing.\n");
        free_tokens(tokens);
        return 1;
    }

    ft_expenser(head);

    printf("\nNodes:\n\n");
    print_node(head);

    free_tokens(tokens);
    free_nodes(head);

    return 0;
}