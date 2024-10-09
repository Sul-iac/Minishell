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

t_token *create_token(char *value, t_token_type type) {
    t_token *new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token) return NULL;  // Check allocation
    new_token->value = strdup(value);
    new_token->type = type;
    new_token->next = NULL;
    return new_token;
}

void append_token(t_token **head, t_token *new_token) {
    if (*head == NULL) {
        *head = new_token;
    } else {
        t_token *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_token;
    }
}

t_token_type determine_type(char *token) {
    if (strcmp(token, "|") == 0) return PIPE;
    if (strncmp(token, ">>", 2) == 0) return REDIR_APPEND;
    if (strncmp(token, ">", 1) == 0) return REDIR_OUT;
    if (strncmp(token, "<<", 2) == 0) return REDIR_HEREDOC;
    if (strncmp(token, "<", 1) == 0) return REDIR_IN;
    return CMD;
}

void skip_spaces(char **input) {
    while (**input == ' ' || **input == '\t') {
        (*input)++;
    }
}

char *extract_quoted_string(char **input) {
    char *start = *input;
    char quote_type = *start;
    char *end = start + 1;

    while (*end && *end != quote_type) {
        if (*end == '\\' && *(end + 1) == quote_type) {
            end++;
        }
        end++;
    }

    if (*end == quote_type) {
        size_t len = end - start + 1;
        char *quoted_string = (char *)malloc(len + 1);
        strncpy(quoted_string, start, len);
        quoted_string[len] = '\0';
        *input = end + 1;
        return quoted_string;
    }

    return NULL;
}

t_token *tokenize_string(char *input) {
    t_token *head = NULL;
    char *ptr = input;

    while (*ptr) {
        skip_spaces(&ptr);
        
        if (*ptr == '\'' || *ptr == '"') {
            char *quoted_token = extract_quoted_string(&ptr);
            if (quoted_token) {
                append_token(&head, create_token(quoted_token, CMD));
                free(quoted_token);
            }
        } else if (*ptr == '|' || *ptr == '<' || *ptr == '>') {
            char operator[3] = {0};
            size_t len = 1;

            if ((*ptr == '>' && *(ptr + 1) == '>') || (*ptr == '<' && *(ptr + 1) == '<')) {
                len = 2;
            }

            strncpy(operator, ptr, len);
            operator[len] = '\0';
            ptr += len;

            skip_spaces(&ptr);
            if (*ptr && *ptr != '|' && *ptr != '<' && *ptr != '>') {
                char *start = ptr;
                while (*ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '|' && *ptr != '<' && *ptr != '>') {
                    ptr++;
                }

                size_t len = ptr - start;
                char *redirection_target = (char *)malloc(len + 1);
                strncpy(redirection_target, start, len);
                redirection_target[len] = '\0';

                char *full_token = (char *)malloc(strlen(operator) + strlen(redirection_target) + 1);
                sprintf(full_token, "%s%s", operator, redirection_target);

                append_token(&head, create_token(full_token, determine_type(operator)));
                free(redirection_target);
                free(full_token);
            }
        } else if (*ptr != '\0') { // Ensure not to process null
            char *start = ptr;
            while (*ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '|' && *ptr != '<' && *ptr != '>') {
                ptr++;
            }

            size_t len = ptr - start;
            char *cmd_token = (char *)malloc(len + 1);
            strncpy(cmd_token, start, len);
            cmd_token[len] = '\0';

            append_token(&head, create_token(cmd_token, CMD));
            free(cmd_token);
        }
    }

    return head;
}

void print_tokens(t_token *head) {
    while (head) {
        printf("[%s] ", head->value);
        head = head->next;
    }
    printf("\n");
}

t_token *reorganize_tokens(t_token *head) {
    t_token *cmd_head = NULL;    
    t_token *cmd_tail = NULL;    
    t_token *other_head = NULL;  
    t_token *other_tail = NULL;  

    t_token *current = head;

    while (current) {
        t_token *next = current->next; // Keep reference to next token
        current->next = NULL;           // Isolate current token

        if (current->type == CMD) {
            if (!cmd_head) {
                cmd_head = current;
                cmd_tail = current;
            } else {
                cmd_tail->next = current;
                cmd_tail = cmd_tail->next;
            }
        } else {
            if (!other_head) {
                other_head = current;
                other_tail = current;
            } else {
                other_tail->next = current;
                other_tail = other_tail->next;
            }
        }

        current = next; // Move to next token
    }

    if (cmd_tail) {
        cmd_tail->next = other_head; // Link CMD tokens to others
    }

    return cmd_head ? cmd_head : other_head; // Return the new head
}

char **split_string(const char *input) {
    // Count the number of substrings
    int num_pipes = 0;
    const char *ptr = input;
    while ((ptr = strchr(ptr, '|')) != NULL) {
        num_pipes++;
        ptr++;
    }
    
    // Allocate memory for the array of strings
    char **str_array = malloc((num_pipes + 2) * sizeof(char *)); // +1 for NULL termination
    if (str_array == NULL) {
        return NULL; // Allocation error
    }

    // Copy substrings into the array
    size_t start = 0; // Use size_t for consistency
    int index = 0;
    while (index <= num_pipes) {
        const char *pipe_pos = strchr(input + start, '|');
        size_t length = (pipe_pos != NULL) ? 
            (size_t)(pipe_pos - (input + start)) : strlen(input + start);  // Cast pointer difference to size_t
        
        // Allocate memory for the substring
        str_array[index] = malloc((length + 1) * sizeof(char));
        if (str_array[index] == NULL) {
            // Free already allocated memory in case of error
            for (int j = 0; j < index; j++) {
                free(str_array[j]);
            }
            free(str_array);
            return NULL;
        }
        
        // Copy the substring
        strncpy(str_array[index], input + start, length);
        str_array[index][length] = '\0'; // Add null terminator
        
        // Update the starting index
        start += length + 1; // +1 to skip the '|' character
        index++;
    }

    str_array[index] = NULL; // NULL terminate the array
    return str_array;
}

void free_tokens(t_token *head) {
    while (head) {
        t_token *temp = head;
        head = head->next;
        free(temp->value); // Free token value
        free(temp); // Free token itself
    }
}

void free_split_array(char **array) {
    for (int i = 0; array[i]; i++) {
        free(array[i]);
    }
    free(array);
}

t_token *concat_tokens(t_token *head1, t_token *head2) {
    if (!head1) return head2; // Si la première liste est vide
    if (!head2) return head1; // Si la deuxième liste est vide

    t_token *current = head1;
    
    // Trouver la fin de la première liste
    while (current->next) {
        current = current->next;
    }

    // Ajouter un token PIPE
    t_token *pipe_token = create_token("|", PIPE);
    current->next = pipe_token;
    
    // Joindre la deuxième liste
    current->next->next = head2;

    return head1; // Retourne la tête de la liste concaténée
}

int main() {
    char *input = "test1  > test2 test3 <<         test4 | < test5 \" <      test6 >>test7\" test8 > test9 test10 | test11";
    char **str = split_string(input);
    
    t_token *final_tokens = NULL; // Liste finale pour les tokens concaténés
    
    for (int j = 0; str[j]; j++) {
        t_token *tokens = tokenize_string(str[j]);
        if (tokens) {
            tokens = reorganize_tokens(tokens); // Réorganiser les tokens
            
            // Concaténer la liste de tokens
            final_tokens = concat_tokens(final_tokens, tokens);
        }
    }
    
    // Affichage de la liste finale
    print_tokens(final_tokens);

    // Libérer la mémoire
    free_tokens(final_tokens); // Libérer la liste finale
    free_split_array(str); // Libérer le tableau divisé
    return 0;
}