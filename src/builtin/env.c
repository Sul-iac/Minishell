/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 23:09:08 by tgerardi          #+#    #+#             */
/*   Updated: 2024/11/10 23:25:45 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env(char ***envp)
{
	int	i;

	if (!*envp)
		free_and_error(NULL, NULL, "env: Env not set", 1);
	i = -1;
	while ((*envp)[++i])
		printf("%s\n", (*envp)[i]);
}
