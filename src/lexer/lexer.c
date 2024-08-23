/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:19:38 by qbarron           #+#    #+#             */
/*   Updated: 2024/08/23 15:57:07 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// il est preferable de faire, je pense, une lookup table.
// ca nous permettra de rechercher beaucoup plus facilement les
// types et valeurs de variables dans un tableau de recherche. 
// voici une video qui explique vraiment bien:
// https://www.youtube.com/watch?v=JPPxV3Hdz_A


// les arguments 0 et 1 permettent de determiner dans l'ordre, le nbr d'options et le nbr d'arguments
commande_infos command_tab[] = {
    {"cd", 0, -1, {NULL}},
    {"pwd", 0, 0, {NULL}},
    {"echo", 1, -1, {"-n"}},                        // -1 = nombre d'arguments illimites
//  nbr d'options et d'args a definir:
    {"export", 0, 0, {NULL}},       
    {"unset", 0, 0, {NULL}},
    {"env", 0, 0, {NULL}},
    {"exit", 0, 0, {NULL}},
// pour les TOKEN_ARGUMENTS(2):

// : faire des if/else, avec le nombre d'arguments a avoir par fonction ? (update: non)
// : creer une fonction de verification de token? --> yessss
};

//cette fonction va chercher la commande demande:
commande_infos *find_command(char *command)
{
    int i = -1;
    int len = sizeof(sizeof(command_tab) / sizeof(commande_infos));
    while(i < len)
    {
        if(strcmp(command_tab[i].command, command) == 0)
            return(&command_tab[i]);
        i++;
    }
    return(NULL);
}

int verification_token(t_token *token, int token_count)
{
    
}

int main(int argc, char **argv)
{
    char *str = argv[1];
    int i = 0;
    int start, end = 0;
    while(str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    char **res = ft_split(str, ' ');
    while(str[i]){
        printf("%s", res[i++]);
    }
}

// 23-08-2023: au final pourquoi ne pas utiliser des fonctions booleennes au lieu de se faire chier ?
// ici la source: https://www.geeksforgeeks.org/c-lexical-analyser-lexer/




// bool is_operator(char c)
// {
//     return(c == '>' || c == '<' || c == '\'' || c == '\"');
// }

// char *lexical_analyser(char *input)
// {
//     int start, end = 0;
//     int len = strlen(input);
//     while(end <= len && start != end)
//     {
//         if(is_delimiter(input[end]))
//             end++;
//         if(is_delimiter(input[end]) && start == end)
//         {
//             if(is_operator(input[end]))
            
//         }
//     }
// }

// int lexer(char *args)
// {
//     lexical_anlyser(args);
// }




// au debut, je comptais faire le code comme ceci, en cherchant chaque valeur
// et en updatant la valeur et le type des t_tokens a chaque occurence d'une 
// commande, sauf que c'est beaucoup trop long. Ducoup je suis 
// partit sur l'idee de la lookup table. 
/*
t_token *lexer(char *str)
{
    int i = 0;
    t_token *token;
    if(!*str)
        return(NULL);
    while(str[i])
    {
        if(str[i] == "cd"){
            token->commands->type = 0;
            token->commands->value = "cd";
        }
        else if(str[i] == "pwd"){
            token->commands->type = 0;
            token->commands->value = "pwd"
        else if
            //...
        }
    }
}*/