/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:09:08 by tgerardi          #+#    #+#             */
/*   Updated: 2024/10/27 12:45:59 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_env(char **envp)
{	
	if(!envp)
		error();
	int i = -1;
	while(envp[++i])
		printf("%s\n", envp[i]);
}