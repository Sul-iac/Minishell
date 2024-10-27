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

t_token *create_token(char *value, t_token_type type)
{
    t_token *new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token) return NULL;
    new_token->value = strdup(value);
    new_token->type = type;
    new_token->next = NULL;
    return new_token;
}

void append_token(t_token **head, t_token *new_token)
{
    if (*head == NULL)
    {
        *head = new_token;
    } else {
        t_token *temp = *head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_token;
    }
}

t_token_type determine_type(char *token)
{
    if (strcmp(token, "|") == 0) return PIPE;
    if (strncmp(token, ">>", 2) == 0) return REDIR_APPEND;
    if (strncmp(token, ">", 1) == 0) return REDIR_OUT;
    if (strncmp(token, "<<", 2) == 0) return REDIR_HEREDOC;
    if (strncmp(token, "<", 1) == 0) return REDIR_IN;
    return CMD;
}

void skip_spaces(char **input)
{
    while (**input == ' ' || **input == '\t')
    {
        (*input)++;
    }
}

char *extract_quoted_string(char **input)
{
    char *start = *input;
    char quote_type = *start;
    char *end = start + 1;

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
        size_t len = end - start + 1;
        char *quoted_string = (char *)malloc(len + 1);
        strncpy(quoted_string, start, len);
        quoted_string[len] = '\0';
        *input = end + 1;
        return quoted_string;
    }

    return NULL;
}

t_token *tokenize_string(char *input)
{
    t_token *head = NULL;
    char *ptr = input;

    while (*ptr)
    {
        skip_spaces(&ptr);

        if (*ptr == '\'' || *ptr == '"')
        {
            char *quoted_token = extract_quoted_string(&ptr);
            if (quoted_token)
            {
                append_token(&head, create_token(quoted_token, CMD));
                free(quoted_token);
            }
        }
        else if (*ptr == '|' || *ptr == '<' || *ptr == '>')
        {
            char operator[3] = {0};
            size_t len = 1;

            if ((*ptr == '>' && *(ptr + 1) == '>') || (*ptr == '<' && *(ptr + 1) == '<'))
            {
                len = 2;
            }

            strncpy(operator, ptr, len);
            operator[len] = '\0';
            ptr += len;

            skip_spaces(&ptr);

            if (*ptr && *ptr != '|' && *ptr != '<' && *ptr != '>')
            {
                char *start = ptr;
                while (*ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '|' && *ptr != '<' && *ptr != '>')
                {
                    ptr++;
                }

                size_t len = ptr - start;
                char *redirection_target = (char *)malloc(len + 1);
                strncpy(redirection_target, start, len);
                redirection_target[len] = '\0';

                append_token(&head, create_token(redirection_target, determine_type(operator)));

                free(redirection_target);
            }
        }
        else if (*ptr != '\0')
        {
            char *start = ptr;
            while (*ptr && *ptr != ' ' && *ptr != '\t' && *ptr != '|' && *ptr != '<' && *ptr != '>')
            {
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

t_token *reorganize_tokens(t_token *head)
{
    t_token *cmd_head = NULL;    
    t_token *cmd_tail = NULL;    
    t_token *other_head = NULL;  
    t_token *other_tail = NULL;  

    t_token *current = head;

    while (current)
    {
        t_token *next = current->next;
        current->next = NULL;

        if (current->type == CMD)
        {
            if (!cmd_head)
            {
                cmd_head = current;
                cmd_tail = current;
            } else {
                cmd_tail->next = current;
                cmd_tail = cmd_tail->next;
            }
        } else {
            if (!other_head)
            {
                other_head = current;
                other_tail = current;
            } else {
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
    return cmd_head ? cmd_head : other_head;
}

char **split_string(const char *input)
{
    int num_pipes = 0;
    const char *ptr = input;
    while ((ptr = strchr(ptr, '|')) != NULL)
    {
        num_pipes++;
        ptr++;
    }
    char **str_array = malloc((num_pipes + 2) * sizeof(char *));
    if (str_array == NULL)
    {
        return NULL;
    }
    size_t start = 0;
    int index = 0;
    while (index <= num_pipes)
    {
        const char *pipe_pos = strchr(input + start, '|');
        size_t length = (pipe_pos != NULL) ? 
            (size_t)(pipe_pos - (input + start)) : strlen(input + start);
        str_array[index] = malloc((length + 1) * sizeof(char));
        if (str_array[index] == NULL)
        {
            for (int j = 0; j < index; j++)
            {
                free(str_array[j]);
            }
            free(str_array);
            return NULL;
        }
        strncpy(str_array[index], input + start, length);
        str_array[index][length] = '\0';
        start += length + 1;
        index++;
    }

    str_array[index] = NULL;
    return str_array;
}

void free_tokens(t_token *head)
{
    while (head)
    {
        t_token *temp = head;
        head = head->next;
        free(temp->value);
        free(temp);
    }
}

void free_split_array(char **array)
{
    for (int i = 0; array[i]; i++)
    {
        free(array[i]);
    }
    free(array);
}

t_token *concat_tokens(t_token *head1, t_token *head2)
{
    if (!head1) return head2;
    if (!head2) return head1;

    t_token *current = head1;

    while (current->next)
    {
        current = current->next;
    }
    t_token *pipe_token = create_token("|", PIPE);
    current->next = pipe_token;
    current->next->next = head2;
    return head1;
}

t_token *group_cmd_tokens(t_token *head)
{
    t_token *grouped_head = NULL;
    t_token *temp = head;

    while (temp)
    {
        if (temp->type == CMD)
        {
            char *grouped_value = strdup(temp->value);
            size_t grouped_len = strlen(grouped_value);
            while (temp->next && temp->next->type == CMD)
            {
                temp = temp->next;
                grouped_len += strlen(temp->value) + 1;
                grouped_value = (char *)realloc(grouped_value, grouped_len + 1);
                strcat(grouped_value, " ");
                strcat(grouped_value, temp->value);
            }
            t_token *new_cmd_token = create_token(grouped_value, CMD);
            append_token(&grouped_head, new_cmd_token);
            free(grouped_value);
        } else {
            append_token(&grouped_head, create_token(temp->value, temp->type));
        }
        temp = temp->next;
    }
    return grouped_head;
}

t_token *lexer(char *input)
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

///////////////////////////// fin du lexer

t_node *create_node(t_node_type type, char *value)
{
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node) return NULL;

    new_node->type = type;
p
    if (value) {
        new_node->value = strdup(value);
        if (!new_node->value) {
            free(new_node);
            return NULL;
        }
    } else {
        new_node->value = NULL;
    }

    new_node->next = NULL;
    new_node->inputs = NULL;
    new_node->outputs = NULL;
    new_node->builtin = false;
    new_node->is_last_cmd = false;

    return new_node;
}

t_redirection *create_redirection(char *filename, bool is_double)
{
    t_redirection *new_redir = (t_redirection *)malloc(sizeof(t_redirection));
    if (!new_redir) return NULL;

    new_redir->filename = strdup(filename);
    new_redir->is_double = is_double;
    new_redir->next = NULL;

    return new_redir;
}

void append_redirection(t_redirection **head, t_redirection *new_redir)
{
    if (*head == NULL)
    {
        *head = new_redir;
    } else {
        t_redirection *temp = *head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = new_redir;
    }
}

t_node *create_node_from_tokens(t_token *tokens)
{
    t_node *node = NULL;
    t_redirection *inputs = NULL;
    t_redirection *outputs = NULL;
    char *cmd_value = NULL;
    
    while (tokens)
    {
        if (tokens->type == CMD)
        {
            if (!cmd_value)
            {
                cmd_value = strdup(tokens->value);
            } else {
                size_t new_len = strlen(cmd_value) + strlen(tokens->value) + 2;
                cmd_value = (char *)realloc(cmd_value, new_len);
                strcat(cmd_value, " ");
                strcat(cmd_value, tokens->value);
            }
        } else if (tokens->type == REDIR_IN || tokens->type == REDIR_HEREDOC)
        {
            append_redirection(&inputs, create_redirection(tokens->value, tokens->type == REDIR_HEREDOC));
        } else if (tokens->type == REDIR_OUT || tokens->type == REDIR_APPEND)
        {
            append_redirection(&outputs, create_redirection(tokens->value, tokens->type == REDIR_APPEND));
        }

        tokens = tokens->next;
    }

    if (cmd_value)
    {
        node = create_node(CMD_2, cmd_value);
        node->inputs = inputs;
        node->outputs = outputs;
        free(cmd_value);
    } else {
        node = create_node(EMPTY_CMD, NULL);
        node->inputs = inputs;
        node->outputs = outputs;
    }

    return node;
}

t_node *convert_tokens_to_nodes(t_token *tokens)
{
    t_node *node_head = NULL;
    t_node *node_tail = NULL;

    t_token *current_token = tokens;
    t_token *cmd_tokens = NULL;

    while (current_token)
    {
        if (current_token->type == PIPE)
        {
            if (cmd_tokens)
            {
                t_node *cmd_node = create_node_from_tokens(cmd_tokens);
                if (!node_head)
                {
                    node_head = cmd_node;
                    node_tail = cmd_node;
                } else {
                    node_tail->next = cmd_node;
                    node_tail = node_tail->next;
                }
                free_tokens(cmd_tokens);
                cmd_tokens = NULL;
            }

            t_node *pipe_node = create_node(PIPE_2, "|");
            node_tail->next = pipe_node;
            node_tail = pipe_node;
        } else {
            append_token(&cmd_tokens, create_token(current_token->value, current_token->type));
        }

        current_token = current_token->next;
    }

    if (cmd_tokens) {
        t_node *cmd_node = create_node_from_tokens(cmd_tokens);
        if (!node_head) {
            node_head = cmd_node;
            node_tail = cmd_node;
        } else {
            node_tail->next = cmd_node;
        }
        free_tokens(cmd_tokens);
    }

    return node_head;
}

t_node *parser(t_token *tokens) {
    if (!tokens) return NULL;
    t_node *head = convert_tokens_to_nodes(tokens);

    return head;
}

///////////////////////////// fin du parsing


bool ft_is_builtin(char *command) {
    if (command == NULL) return false;
    
    const char *builtins[] = {"echo ", "cd ", "pwd ", "export ", "unset ", "env ", "exit "};
    unsigned long i = 0;

    while (i < 7) {
        if (strstr(command, builtins[i]) != NULL) {
            return true;
        }
        i++;
    }
    return false;
}

void mark_builtins(t_node *head) {
    t_node *current = head;

    while (current != NULL) {
        if (ft_is_builtin(current->value)) {
            current->builtin = true;
        } else {
            current->builtin = false;
        }
        current = current->next;
    }
}

void ft_is_last_cmd(t_node *head) {
    if (head == NULL) {
        return;
    }

    t_node *current = head;

    while (current != NULL) {
        if (current->next == NULL) {
            current->is_last_cmd = 1;
        } else {
            current->is_last_cmd = 0;
        }
        current = current->next;
    }
}

char *expand_env_variables(const char *input) {
    size_t result_size = 1024;
    char *result = (char *)malloc(result_size);
    if (!result) return NULL;

    size_t i = 0;
    size_t j = 0;

    while (input[i] != '\0') {
        if (input[i] == '$' && (input[i+1] != ' ' && input[i+1] != '\t' && input[i+1] != '\0')) {
            i++;
            size_t var_len = 0;
            while (input[i + var_len] && (input[i + var_len] != ' ' && input[i + var_len] != '\t' && input[i + var_len] != '$')) {
                var_len++;
            }

            char *var_name = strndup(&input[i], var_len);
            if (!var_name) {
                free(result);
                return NULL;
            }
            char *var_value = getenv(var_name);
            free(var_name);

            if (var_value) {
                size_t value_len = strlen(var_value);
                if (j + value_len >= result_size) {
                    result_size *= 2;
                    result = (char *)realloc(result, result_size);
                    if (!result) return NULL;
                }
                strcpy(&result[j], var_value);
                j += value_len;
            }
            i += var_len;
        } else {
            result[j++] = input[i++];
        }
    }

    result[j] = '\0';
    return result;
}

void expand_node_values(t_node *head) {
    t_node *current = head;
    while (current != NULL) {
        if (current->type == CMD_2 && current->value != NULL) {
            char *expanded_value = expand_env_variables(current->value);
            if (expanded_value) {
                free(current->value);
                current->value = expanded_value;
            }
        }
        current = current->next;
    }
}

void free_nodes(t_node *head)
{
    while (head)
    {
        t_node *temp = head;
        head = head->next;
        
        if (temp->value)
        {
            free(temp->value);
        }
        
        t_redirection *input = temp->inputs;
        while (input)
        {
            t_redirection *temp_input = input;
            input = input->next;
            free(temp_input->filename);
            free(temp_input);
        }

        t_redirection *output = temp->outputs;
        while (output)
        {
            t_redirection *temp_output = output;
            output = output->next;
            free(temp_output->filename);
            free(temp_output);
        }

        free(temp);
    }
}
void ft_expenser(t_node *head)
{
    mark_builtins(head);
    ft_is_last_cmd(head);
    expand_node_values(head);
}

void print_token(t_token *token) {
    while (token) {
        printf("Token Value: '%s', Type: %d\n", token->value, token->type);
        token = token->next;
    }
}

void print_redirection(t_redirection *redir) {
    while (redir) {
        printf("\tRedirection Filename: '%s', Is Double: %d\n", redir->filename, redir->is_double);
        redir = redir->next;
    }
}

void print_node(t_node *node) {
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

int main() {
    char *input = "echohello $USER | grep h";

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