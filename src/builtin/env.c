/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:09:08 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/02 15:56:13 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_env(char ***envp)
{	
	if(!*envp)
		free_and_error(NULL, NULL, "env: Env not set", 1);
	int i = -1;
	while((*envp)[++i])
		printf("%s\n", (*envp)[i]);
}