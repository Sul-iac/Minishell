/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:19:38 by qbarron           #+#    #+#             */
/*   Updated: 2024/08/21 22:11:35 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// il est preferable de faire, je pense, une lookup table.
// ca nous permettra de rechercher beaucoup plus facilement les
// types et valeurs de variables dans un tableau de recherche. 
// voici une video qui explique vraiment bien:
// https://www.youtube.com/watch?v=JPPxV3Hdz_A


// les arguments 0 et 1 permettent de determiner dans l'ordre, le nbr d'options et le nbr d'arguments
t_token *lookup_table[] = {
    {"cd", 0, 1},
    {"pwd", 0, 0},
    {"echo", 1, -1},                        // -1 = nombre d'arguments illimites
// nbr d'options et d'args a definir:
    {"export", 0, 0},       
    {"unset", 0, 0},
    {"env", 0, 0},
    {"exit", 0, 0},
// pour les TOKEN_ARGUMENTS(2):

// : faire des if/else, avec le nombre d'arguments a avoir par fonction ? (update: non)
// : creer une fonction de verification de token? --> yessay
}





// au debut, je comptais faire le code comme ceci, en cherchant chaque valeur
// et en updatant la valeur et le type des t_tokens a chaque occurencer d'une 
// commande, sauf que c'est beaucoup trop long et chiant. Ducoup je suis 
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