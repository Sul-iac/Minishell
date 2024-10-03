/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qbarron <qbarron@student.42perpignan.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:11:47 by qbarron           #+#    #+#             */
/*   Updated: 2024/10/03 12:22:20 by qbarron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


t_node *test_cmd(t_node_type type, char *value, 
					t_redirection *inputs, t_redirection *outputs, 
					bool builtin, bool is_last_cmd)
{
	t_node *node = malloc(sizeof(t_node));
	node->type = type;
	node->value = strdup(value);
	node->inputs = NULL;
	node->outputs = NULL;
	node->builtin = builtin;
	node->is_last_cmd = is_last_cmd;
	node->next = NULL;
	return(node);
}

void exec_test()
{
	t_node *cmd1 = create_node(CMD, "echo", true, false);
	t_node *cmd2 = create_node(CMD, "-n Hello World", true, true);
	cmd1->next = cmd2;
	exec(cmd1);
}

int main(void)
{
	exec_test();
	return(0);
}