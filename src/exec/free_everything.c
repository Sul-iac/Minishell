/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgerardi <tgerardi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 17:45:01 by qbarron           #+#    #+#             */
/*   Updated: 2024/11/12 18:30:29 by tgerardi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_everything(char **env, t_node *head)
{
	clear_history();
	rl_clear_history();
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (head)
		clean_nodes(head);
	if (env)
		ft_free_array(env);
	rl_reset_terminal(NULL);
}
