/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 22:09:06 by tgerardi          #+#    #+#             */
/*   Updated: 2024/08/24 22:09:06 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_exit(char *line)
{
    if (strcmp(line, "exit\n") == 0)
    {
        free(line);
        exit(EXIT_SUCCESS);
    }
}
