/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:19:38 by qbarron           #+#    #+#             */
/*   Updated: 2024/08/21 17:01:01 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// il est preferable de faire, je pense, une lookup table.
// ca nous permettra de rechercher beaucoup plus facilement les
// types et valeurs de variables dans un tableau de recherche. 
// voici une video qui explique vraiment bien:
// https://www.youtube.com/watch?v=JPPxV3Hdz_A

t_token *lookup_table[] = {
    {"cd", 0},
    {"pwd", 0},
    {"echo", 0},
    {"export", 0},
    {"unset", 0},
    {"env", 0},
    {"exit", 0},
    {"-n", 1},          //-n etant la seule option de commande
// pour les TOKEN_ARGUMENTS(2):
// - [ ] cd : on va devoir trouver un moyen de transformer le chemin r/a en token, avec getcwd() ? 
// - [ ] echo ou tout autre commande necessitant un argument. Comment faire pour tokeniser ca ?
}

// le but de la fonction est de parcourir la commande jusqu'a un delimiteur donne





// au debut, je comptais faire le code comme ceci, en cherchant chaque valeur
// et en updatant la valeur et le type des t_tokens a chaque occurencer d'une 
// commande, sauf que c;est beaucoup trop long et chiant. Ducoup je suis 
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