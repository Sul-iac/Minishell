/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:09:16 by tgerardi          #+#    #+#             */
/*   Updated: 2024/08/24 22:09:16 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void ft_unset(int argc, char **argv, char **envp)
{
    int i = 1;
    size_t key_len;
    int j;
    int found;

    while (i < argc)
    {
        key_len = strlen(argv[i]);
        j = 0;
        found = 0;

        while (envp[j] != NULL)
        {
            if (strncmp(envp[j], argv[i], key_len) == 0 && envp[j][key_len] == '=')
            {
                found = 1;
                break;
            }
            j++;
        }
        if (found)
        {
            free(envp[j]);
            while (envp[j] != NULL)
            {
                envp[j] = envp[j + 1];
                j++;
            }
        }
        i++;
    }
}

